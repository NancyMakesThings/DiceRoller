// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DICEROLLER_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	class UButton* CameraMode;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UButton* CameraHome;

	UFUNCTION()
	void ToggleCameraMode();
	UFUNCTION()
	void CameraGoHome();

	bool bCameraMode;
};
