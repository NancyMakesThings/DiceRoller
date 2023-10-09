// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "PlayerCamera.h"

AMyGameModeBase::AMyGameModeBase()
{
    UE_LOG(LogTemp, Warning, TEXT("MyGameModeBase Constructor"));
    
    // Reference to BP_PlayerController. Note that this needs an update if the reference path changes!
    static ConstructorHelpers::FClassFinder<AMyPlayerController> BPPlayerController(TEXT("/Game/DiceRoller/Core/Player/PC_DiceRoller.PC_DiceRoller_C"));
    if (BPPlayerController.Succeeded())
    {
        PlayerControllerClass = BPPlayerController.Class;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MyGameModeBase Constructor: PlayerControllerClass not set"));
    }

    // Reference to BP_PlayerCamera. Note that this needs an update if the reference path changes!
    static ConstructorHelpers::FClassFinder<APlayerCamera> BPPlayerCamera(TEXT("/Game/DiceRoller/Core/Player/BP_PlayerCamera.BP_PlayerCamera_C"));
    if (BPPlayerCamera.Succeeded())
    {
        DefaultPawnClass = BPPlayerCamera.Class;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MyGameModeBase Constructor: DefaultPawnClass not set"));
    }
    

    //PlayerControllerClass = APlayerController::StaticClass();
    //DefaultPawnClass = APlayerCamera::StaticClass();
   
}

void AMyGameModeBase::BeginPlay()
{
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