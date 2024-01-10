// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

// forward declarations
class UComboBoxString;

/**
 * 
 */
UCLASS()
class DICEROLLER_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// Camera variables
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UButton* Camera;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UButton* CameraHome;

	// Camera functions
	UFUNCTION(BlueprintCallable)
	void ToggleCameraMode();
	UFUNCTION(BlueprintCallable)
	void CameraGoHome();

	// Dropdown menu handling
	UFUNCTION(BlueprintCallable)
	void PopulateDropdownMenu(const TArray<FString> & Names, const UMaterialInstanceDynamic * const Mat, UComboBoxString * ComboBox);
	
};
