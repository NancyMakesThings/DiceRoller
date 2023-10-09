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

void AMyPlayerController::SetupInputComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::SetupInputComponent() Started"));

	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) 
	{
		EnhancedInputComponent->BindAction(DiceMoveAction, ETriggerEvent::Started, this, &AMyPlayerController::DiceDrag);
		EnhancedInputComponent->BindAction(DiceMoveAction, ETriggerEvent::Completed, this, &AMyPlayerController::DiceDrop);

		// Bind camera input
		if (APlayerCamera* Camera = Cast<APlayerCamera>(GetPawn()))
		{
			UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::SetupInputComponent() Bind Camera Input"));
			EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Triggered, Camera, &APlayerCamera::Zoom);
		}
		else if (GetPawn() == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::SetupInputComponent() No Pawn "));
		}
	}
}

void AMyPlayerController::DiceDrag()
{
	// Allow dice to be moved with mouse via physics handle
	UE_LOG(LogTemp, Warning, TEXT("IA_DiceMove started"));

	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
	ADice* Dice = Cast<ADice>(HitResult.GetActor());
	if (Dice != nullptr)
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
