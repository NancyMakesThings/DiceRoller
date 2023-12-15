// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DiceProperties.h"
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

protected:
	
	virtual void Init() override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	FDiceProperties CurrentProp;

};
