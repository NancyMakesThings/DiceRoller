// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UPhysicsHandleComponent;

/**
 * 
 */
UCLASS()
class DICEROLLER_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Components")
	UPhysicsHandleComponent* GetPhysicsHandle() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Input
	void SetupInputComponent() override;
	void DiceDrag();
	void DiceDrop();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DiceRollerMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* DiceMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* CameraZoomAction;

	// Update dice location
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float GrabLocationZ = 800;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OriginalDistanceToObject;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPhysicsHandleComponent* PhysicsHandle;
};
