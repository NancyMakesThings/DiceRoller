// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DICEROLLER_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    AMyGameModeBase();

    // Remove the current menu widget and create a new one from the specified class, if provided
    UFUNCTION(BlueprintCallable, Category = "Widget")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    // The widget class we will use as our menu when the game starts
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
    TSubclassOf<UUserWidget> StartingWidgetClass;

    // The widget instance that we are using as our menu
    UPROPERTY()
    UUserWidget* CurrentWidget;
};
