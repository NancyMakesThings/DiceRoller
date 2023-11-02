// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MeshStyle.h"
#include "DiceType.h"
#include "MyGameInstance.generated.h"

// Forward declarations
class APreview;
class UObjectLibrary;

/**
 * Custom subclass of GameInstance. 
 * Handles material and mesh selections (persistent throughout game instance)
 */
UCLASS()
class DICEROLLER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	// Current materials
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* CurrentMatDiceFace;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* CurrentMatDiceNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* CurrentMatTray;
	
	// Dynamic material instances for preview meshes in settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstanceDynamic* PreviewDynMatDiceFace;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstanceDynamic* PreviewDynMatDiceNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstanceDynamic* PreviewDynMatTray;

	// Current mesh style
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	MeshStyle CurrentMeshStyle;

	// Preview mesh style
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	MeshStyle PreviewMeshStyle;

	// Preview dice type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	DiceType PreviewDiceType;

protected:
	virtual void Init() override;


};
