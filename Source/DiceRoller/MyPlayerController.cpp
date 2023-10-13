// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Dice.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PlayerCamera.h"

AMyPlayerController::AMyPlayerController()
{
	// UE_LOG(LogTemp, Warning, TEXT("MyPlayerController Constructor"));
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	// Enable mouse events
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// Enable touch events
	bEnableTouchEvents = true;
	bEnableTouchOverEvents = true;
}

// Called when the game starts or when spawned
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set input mode and ensure mouse is movable during click
	FInputModeGameAndUI inputMode;
	inputMode.SetHideCursorDuringCapture(false);
	SetInputMode(inputMode);
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DiceRollerMappingContext,0);
	}
}

// Called every frame
void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update grabbed dice position
	if (PhysicsHandle->GrabbedComponent != NULL)
	{
		FVector MouseLocation, MouseDirection, NewDiceLocation;
		DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

		NewDiceLocation = MouseLocation + MouseDirection * OriginalDistanceToObject;
		NewDiceLocation.Z = GrabLocationZ; // Use fixed grab Z location

		PhysicsHandle->SetTargetLocation(NewDiceLocation);
		// UE_LOG(LogTemp, Warning, TEXT("IA_DiceMove started %s"), *NewDiceLocation.ToString());
	}

}

UPhysicsHandleComponent* AMyPlayerController::GetPhysicsHandle() const
{
	return PhysicsHandle;
}

UInputMappingContext* AMyPlayerController::GetDiceMappingContext() const
{
	return DiceRollerMappingContext;
}

UInputMappingContext* AMyPlayerController::GetCameraMappingContext() const
{
	return CameraMappingContext;
}

void AMyPlayerController::SetupInputComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::SetupInputComponent() Started"));

	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) 
	{
		EnhancedInputComponent->BindAction(DiceMoveAction, ETriggerEvent::Started, this, &AMyPlayerController::DiceDrag);
		EnhancedInputComponent->BindAction(DiceMoveAction, ETriggerEvent::Completed, this, &AMyPlayerController::DiceDrop);
		EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &AMyPlayerController::PlayerCameraZoom);
		EnhancedInputComponent->BindAction(CameraRotateAction, ETriggerEvent::Triggered, this, &AMyPlayerController::PlayerCameraRotate);
		EnhancedInputComponent->BindAction(CameraPanAction, ETriggerEvent::Started, this, &AMyPlayerController::PlayerCameraPanStart);
		EnhancedInputComponent->BindAction(CameraPanAction, ETriggerEvent::Completed, this, &AMyPlayerController::PlayerCameraPanStop);
		EnhancedInputComponent->BindAction(CameraCenterAction, ETriggerEvent::Triggered, this, &AMyPlayerController::PlayerCameraCenter);
	}
}

// Allow dice to be moved with mouse via physics handle
void AMyPlayerController::DiceDrag()
{
	UE_LOG(LogTemp, Warning, TEXT("IA_DiceMove started"));

	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
	if (ADice* Dice = Cast<ADice>(HitResult.GetActor()))
	{
		OriginalDistanceToObject = HitResult.Distance;
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitComponent->GetCenterOfMass(), HitComponent->GetOwner()->GetActorRotation());
	}
}

void AMyPlayerController::DiceDrop()
{
	UE_LOG(LogTemp, Warning, TEXT("IA_DiceMove completed"));

	if (PhysicsHandle->GrabbedComponent != NULL)
	{
		if (ADice* Dice = Cast<ADice>(PhysicsHandle->GrabbedComponent->GetOwner()))
		{
			Dice->RandomFall();
		}
		PhysicsHandle->ReleaseComponent();
	}
}

void AMyPlayerController::PlayerCameraZoom(const FInputActionValue& Value)
{
	if (APlayerCamera* PlayerCamera = Cast<APlayerCamera>(GetPawn()))
	{
		PlayerCamera->Zoom(Value);
	}
}

void AMyPlayerController::PlayerCameraRotate(const FInputActionValue& Value)
{
	if (APlayerCamera* PlayerCamera = Cast<APlayerCamera>(GetPawn()))
	{
		PlayerCamera->Rotate(Value);
	}
}

void AMyPlayerController::PlayerCameraPanStart()
{
	if (APlayerCamera* PlayerCamera = Cast<APlayerCamera>(GetPawn()))
	{
		PlayerCamera->PanStart();
	}
}

void AMyPlayerController::PlayerCameraPanStop()
{
	if (APlayerCamera* PlayerCamera = Cast<APlayerCamera>(GetPawn()))
	{
		PlayerCamera->PanStop();
	}
}

// Center camera on clicked dice location
void AMyPlayerController::PlayerCameraCenter()
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
	if (ADice* Dice = Cast<ADice>(HitResult.GetActor()))
	{
		FVector TargetLocation = HitResult.GetComponent()->GetCenterOfMass();
		if (APlayerCamera* PlayerCamera = Cast<APlayerCamera>(GetPawn()))
		{
			PlayerCamera->Center(TargetLocation);
		}
	}
}
