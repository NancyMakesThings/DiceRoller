// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "Properties.h"
#include "MyGameUserSettings.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DICEROLLER_API UMyGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void UpdatePreset(const FDiceProperties & NewProp);

	UFUNCTION(BlueprintCallable)
	void UpdateColor(FLinearColor Color);

protected: 

	UPROPERTY(Config, BlueprintReadOnly)
	FDiceProperties SavedPreset1;

	UPROPERTY(Config, BlueprintReadOnly)
	FLinearColor ColorTest;
	
};
