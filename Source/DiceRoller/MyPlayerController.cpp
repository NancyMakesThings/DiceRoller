// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{
	// UE_LOG(LogTemp, Warning, TEXT("MyPlayerController Constructor"));
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

}

// Called when the game starts or when spawned
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsGrabbingComponent)
	{
		FVector MouseLocation, MouseDirection, NewDiceLocation;
		DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

		NewDiceLocation = MouseLocation + MouseDirection * OriginalDistanceToObject;
		NewDiceLocation.Z = GrabLocationZ;

		PhysicsHandle->SetTargetLocation(NewDiceLocation);
	}

}

