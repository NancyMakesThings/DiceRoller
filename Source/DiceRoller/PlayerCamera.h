// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerCamera.generated.h"

// Forward declarations
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DICEROLLER_API APlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCamera();

	// Camera actions
	void Zoom(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
	void PanStart();
	void PanStop();
	void Center(FVector TargetLocation);
	void Home();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Camera Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComp;
	
	// Camera variables
	FVector StartLocation;
	FRotator StartRotation;
	FVector HomeLocation;
	float StartArmLength;
	const float MaxX = 2000.0f;
	const float MinX = -2000.0f;
	const float MaxY = 2000.0f;
	const float MinY = -2000.0f;
	const float MaxZ = 2000.0f;
	const float MinZ = -2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZoomInterval = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ArmClampMin = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ArmClampMax = 4000;

	bool bEnablePan;
	FVector2D PreviousPanPosition;


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
