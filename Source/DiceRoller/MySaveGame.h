// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Properties.h"
#include "DiceType.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DICEROLLER_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	//UMySaveGame();

	UPROPERTY(VisibleAnywhere, Category = "Dice Properties")
	FDiceProperties SavedPreset1;

	UPROPERTY(VisibleAnywhere, Category = "Tray Properties")
	FTrayProperties SavedTray;

	UPROPERTY(BlueprintReadOnly, Category = "Dice Properties")
	TArray<FDiceProperties> SavedDiceProp;
	
	UPROPERTY(BlueprintReadOnly, Category = "Dice Properties")
	TArray<DiceType> SavedDiceType;

	UPROPERTY(BlueprintReadWrite, Category = "Camera Properties")
	bool bHideCameraTooltip = false;

	UPROPERTY(BlueprintReadWrite, Category = "Dice Properties")
	int DiceCount = 1; // game loads one die on start


};
