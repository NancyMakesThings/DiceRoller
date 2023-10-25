// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "PlayerCamera.h"

AMyGameModeBase::AMyGameModeBase()
{
    UE_LOG(LogTemp, Warning, TEXT("MyGameModeBase Constructor"));

    // Overwritten in Blueprint child class to link BP and C++.
    PlayerControllerClass = APlayerController::StaticClass();
    DefaultPawnClass = APlayerCamera::StaticClass();
   
}

void AMyGameModeBase::BeginPlay()
{
    UE_LOG(LogTemp, Warning, TEXT("MyGameModeBase BeginPlay"));

    Super::BeginPlay();
    ChangeMenuWidget(StartingWidgetClass);
}

void AMyGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}
