// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameUserSettings.h"

void UMyGameUserSettings::UpdatePreset(const FDiceProperties& NewProp)
{
	SavedPreset1 = NewProp;
}

void UMyGameUserSettings::UpdateColor(FLinearColor Color)
{
	ColorTest = Color;
}
