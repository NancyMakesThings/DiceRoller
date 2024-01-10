// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "PlayerCamera.h"
#include "GameFramework/GameUserSettings.h"

AMyGameModeBase::AMyGameModeBase()
{
    UE_LOG(LogTemp, Warning, TEXT("MyGameModeBase Constructor"));

    // Overwritten in Blueprint child class to link BP and C++.
    PlayerControllerClass = APlayerController::StaticClass();
    DefaultPawnClass = APlayerCamera::StaticClass();

    if (GEngine)
    {
        UGameUserSettings* MyGameSettings = GEngine->GetGameUserSettings();
        MyGameSettings->SetFullscreenMode(EWindowMode::Windowed);
        MyGameSettings->SetScreenResolution(FIntPoint(1280, 720));
        MyGameSettings->SetVSyncEnabled(true);
        MyGameSettings->ApplySettings(true);
    }
    
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
