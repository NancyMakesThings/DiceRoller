// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dice.generated.h"

class UStaticMeshComponent;

UCLASS()
class DICEROLLER_API ADice : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice")
	float AngularImpulseMagnitude = 360;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DiceMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void RandomFall();
};
