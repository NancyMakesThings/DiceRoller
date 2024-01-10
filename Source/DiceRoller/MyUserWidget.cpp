// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Components/Button.h"
#include "EnhancedInputSubsystems.h"
#include "MyPlayerController.h"
#include "PlayerCamera.h"
#include "Components/ComboBoxString.h"
#include "MyGameInstance.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Camera != nullptr)
	{
		Camera->OnClicked.AddUniqueDynamic(this, &UMyUserWidget::ToggleCameraMode);
	}
	if (CameraHome != nullptr)
	{
		CameraHome->OnClicked.AddUniqueDynamic(this, &UMyUserWidget::CameraGoHome);
	}
}


void UMyUserWidget::ToggleCameraMode()
{
	UE_LOG(LogTemp, Warning, TEXT("ToggleCameraMode"))

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningLocalPlayer()))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetOwningPlayer()))
		{

			if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
			{
				if (Game->bCameraMode)
				{
					UE_LOG(LogTemp, Warning, TEXT("ToggleCameraMode False"))
					Game->bCameraMode = false;
					Subsystem->AddMappingContext(PlayerController->GetDiceMappingContext(), 0);
					Subsystem->RemoveMappingContext(PlayerController->GetCameraMappingContext());
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("ToggleCameraMode True"))
					Game->bCameraMode = true;
					Subsystem->AddMappingContext(PlayerController->GetCameraMappingContext(), 0);
					Subsystem->RemoveMappingContext(PlayerController->GetDiceMappingContext());
				}
			}

		}
		
	}
}

void UMyUserWidget::CameraGoHome()
{
	if (APlayerCamera* PlayerCamera = Cast<APlayerCamera>(GetOwningPlayerPawn()))
	{
		PlayerCamera->Home();
	}
}

void UMyUserWidget::PopulateDropdownMenu(const TArray<FString>& Names, const UMaterialInstanceDynamic * const Mat, UComboBoxString * ComboBox)
{

	for (FString elem : Names)
	{
		ComboBox->AddOption(elem); 
	}
	FString SplitOn = "_";
	FString Left, Right;
	Mat->Parent.GetName().Split(TEXT("_"), &Left, &Right);
	ComboBox->SetSelectedOption(Right);

}

