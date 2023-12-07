// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Preview.generated.h"

// Forward declarations
class USceneCaptureComponent2D;
class USpringArmComponent;

UCLASS()
class DICEROLLER_API APreview : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APreview();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Scene capture components
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	USceneCaptureComponent2D* SceneCaptureTray;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	USceneCaptureComponent2D* SceneCaptureDice;

	// Spring arm components
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	USpringArmComponent* SpringArmTray;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	USpringArmComponent* SpringArmDice;

	// Static mesh components
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	UStaticMeshComponent* MeshTray;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	UStaticMeshComponent* MeshDice;

	// Update mesh
	UFUNCTION(BlueprintCallable)
	void UpdateDiceMesh(UStaticMesh* NewMesh);

	// Materials library handling
	UFUNCTION(BlueprintCallable)
	void UpdateDiceFaceMat();


};
