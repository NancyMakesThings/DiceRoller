// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Dice.h"
#include "Kismet/KismetMathLibrary.h"

AMyPlayerController::AMyPlayerController()
{
	// UE_LOG(LogTemp, Warning, TEXT("MyPlayerController Constructor"));
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

}

// Called when the game starts or when spawned
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
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
		NewDiceLocation.Z = GrabLocationZ;

		PhysicsHandle->SetTargetLocation(NewDiceLocation);
	}

}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(DiceMoveAction, ETriggerEvent::Started, this, &AMyPlayerController::DiceDrag);
		EnhancedInputComponent->BindAction(DiceMoveAction, ETriggerEvent::Completed, this, &AMyPlayerController::DiceDrop);
	}	
}

void AMyPlayerController::DiceDrag()
{
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
		FVector Impulse = FVector(UKismetMathLibrary::RandomFloatInRange(-1, 1), UKismetMathLibrary::RandomFloatInRange(-1, 1), UKismetMathLibrary::RandomFloatInRange(-1, 1));
		Impulse = Impulse * AngularImpulseMagnitude;
		PhysicsHandle->GrabbedComponent->AddAngularImpulseInDegrees(Impulse, NAME_None, true);
		PhysicsHandle->ReleaseComponent();
	}
}
