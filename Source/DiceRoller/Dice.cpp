// Fill out your copyright notice in the Description page of Project Settings.


#include "Dice.h"
#include "MyPlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADice::ADice()
{
	UE_LOG(LogTemp, Warning, TEXT("Dice Constructor"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DiceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyDiceMesh"));
	RootComponent = DiceMesh;

	DiceMesh->SetSimulatePhysics(true);
	DiceMesh->SetEnableGravity(true);

}

// Called when the game starts or when spawned
void ADice::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Dice BeginPlay"));

	Super::BeginPlay();

	RandomFall();
}

void ADice::RandomFall()
{
	UE_LOG(LogTemp, Warning, TEXT("ADice::RandomFall started"));
	
	// Add random angular impulse on dice drop
	FVector Impulse = FVector(UKismetMathLibrary::RandomFloatInRange(-1, 1), UKismetMathLibrary::RandomFloatInRange(-1, 1), UKismetMathLibrary::RandomFloatInRange(-1, 1));
	Impulse = Impulse * AngularImpulseMagnitude;
	DiceMesh->AddAngularImpulseInDegrees(Impulse, NAME_None, true);
}

// Called every frame
void ADice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

