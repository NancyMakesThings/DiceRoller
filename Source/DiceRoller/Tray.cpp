// Fill out your copyright notice in the Description page of Project Settings.


#include "Tray.h"

// Sets default values
ATray::ATray()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATray::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Tray BeginPlay"));	
}

// Called every frame
void ATray::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

