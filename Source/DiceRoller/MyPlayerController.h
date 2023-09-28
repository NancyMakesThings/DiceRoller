// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DICEROLLER_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float GrabLocationZ = 800;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OriginalDistanceToObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsGrabbingComponent = false;
	UPROPERTY(EditDefaultsOnly, Category = "Components", BlueprintReadWrite)
	UPhysicsHandleComponent* PhysicsHandle;

};
