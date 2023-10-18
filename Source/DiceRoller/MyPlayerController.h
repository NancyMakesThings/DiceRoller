// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
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

	UInputMappingContext* GetDiceMappingContext() const;
	UInputMappingContext* GetCameraMappingContext() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Input
	void SetupInputComponent() override;

	// Global
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* GlobalMappingContext;

	// Dice
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DiceRollerMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* DiceMoveAction;

	void DiceDrag();
	void DiceDrop();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dice")
	float GrabLocationZ = 800;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice")
	float OriginalDistanceToObject;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dice")
	UPhysicsHandleComponent* PhysicsHandle;

	// PlayerCamera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UInputMappingContext* CameraMappingContext;

	void PlayerCameraZoom(const FInputActionValue& Value);	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UInputAction* CameraZoomAction;

	void PlayerCameraRotate(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UInputAction* CameraRotateAction;

	void PlayerCameraPanStart();
	void PlayerCameraPanStop();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UInputAction* CameraPanAction;

	void PlayerCameraCenter();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UInputAction* CameraCenterAction;


};
