// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Properties.h"
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
};
