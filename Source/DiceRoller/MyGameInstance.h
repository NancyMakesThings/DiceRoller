// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * Custom subclass of GameInstance. 
 * Handles material selections (persistent throughout game instance)
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

};
