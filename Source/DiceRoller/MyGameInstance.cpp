// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"
#include "EngineUtils.h"
#include "Dice.h"

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance Init"));

    bool PreviousSaveExists = LoadSave();
    CreateDynMatFromCurrent(PreviousSaveExists);
}

void UMyGameInstance::Shutdown()
{
    WriteSave();
    Super::Shutdown();
}

FDiceProperties UMyGameInstance::GetCurrentDiceProp() const
{
    return CurrentDiceProp;
}

FTrayProperties UMyGameInstance::GetCurrentTrayProp() const
{
    return CurrentTrayProp;
}

void UMyGameInstance::UpdateCurrentDiceProp(const FDiceProperties & NewProp)
{
    CurrentDiceProp = NewProp;
}

void UMyGameInstance::UpdateCurrentTrayProp(const FTrayProperties & NewProp)
{
    CurrentTrayProp = NewProp;
}

void UMyGameInstance::UpdatePreset(const FDiceProperties & NewProp, int Index)
{
    CurrentPresets[Index] = NewProp;
}

bool UMyGameInstance::LoadSave()
{
    if (UGameplayStatics::DoesSaveGameExist(SaveName, 0))
    {

        CurrentSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));
        if (CurrentSave != nullptr)
        {
            // Successful load
            UE_LOG(LogTemp, Warning, TEXT("MyGameInstance: Loaded save"));
        
            CurrentDiceProp = CurrentSave->SavedPreset1;
            CurrentTrayProp = CurrentSave->SavedTray;
            return true;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("MyGameInstance: Failed to load save"));
            return false;
        }
    }
    else
    {
        CurrentSave = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
        return false;
    }
}

void UMyGameInstance::WriteSave()
{
    if (CurrentSave != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("MyGameInstance: WriteSave"));

        // Clear dice from previous save to avoid duplicates
        CurrentSave->SavedDiceProp.Empty();
        CurrentSave->SavedDiceType.Empty();

        // Get all dice in world and update SavedDice
        for (FActorIterator It(GetWorld()); It; ++It)
        {
            if(ADice* Dice = Cast<ADice>(*It))
            {
                CurrentSave->SavedDiceProp.Add(Dice->Properties);
                CurrentSave->SavedDiceType.Add(Dice->Type);                                
            }
        }

        // Update save to currently selected dice and tray properties
        SetDicePropSafe(CurrentSave->SavedPreset1);
        CurrentSave->SavedTray = CurrentTrayProp;
        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentTrayProp.Mat))
        {
            CurrentSave->SavedTray.Mat = Mat->Parent;
        }

        // Save game
        UGameplayStatics::SaveGameToSlot(CurrentSave, SaveName, 0);

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MyGameInstance: Failed to write to save"));
    }

}

void UMyGameInstance::CreateDynMatFromCurrent(bool PreviousSaveExists)
{

    // Create current dynamic material instances from default or save file
    CurrentDiceProp.MatFace = UMaterialInstanceDynamic::Create(CurrentDiceProp.MatFace, this);
    CurrentDiceProp.MatNum = UMaterialInstanceDynamic::Create(CurrentDiceProp.MatNum, this);
    CurrentTrayProp.Mat = UMaterialInstanceDynamic::Create(CurrentTrayProp.Mat, this);

    if (CurrentDiceProp.MatFace == nullptr || CurrentDiceProp.MatNum == nullptr || CurrentTrayProp.Mat == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance Init: Post LoadSave, create dynamic materials failed"));
    }

    // if previous save does not exist, align CurrentDiceProp and CurrentTrayPop to default material color
    if (!PreviousSaveExists)
    {
        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentDiceProp.MatFace))
        {
            CurrentDiceProp.ColorFace = Mat->K2_GetVectorParameterValue("BaseColor");
        }

        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentDiceProp.MatNum))
        {
            CurrentDiceProp.ColorNum = Mat->K2_GetVectorParameterValue("BaseColor");
        }

        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentTrayProp.Mat))
        {
            CurrentTrayProp.Color = Mat->K2_GetVectorParameterValue("BaseColor");
        }
    }
    // otherwise, update dynamic material color to saved CurrentDiceProp and CurrentTrayProp colors
    else
    {
        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentDiceProp.MatFace))
        {
            Mat->SetVectorParameterValue("BaseColor", CurrentDiceProp.ColorFace);
            Mat->SetVectorParameterValue("DiffuseColor", CurrentDiceProp.ColorFace); // account for differences in naming for different materials
        }

        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentDiceProp.MatNum))
        {
            Mat->SetVectorParameterValue("BaseColor", CurrentDiceProp.ColorNum);
        }

        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentTrayProp.Mat))
        {
            Mat->SetVectorParameterValue("BaseColor", CurrentTrayProp.Color);
        }
    }
}

// Make sure mats are references parent materials and NOT dynamic materials
 void UMyGameInstance::SetDicePropSafe(FDiceProperties & PropIn)
 {
     PropIn = CurrentDiceProp;
     if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentDiceProp.MatFace))
     {
         PropIn.MatFace = Mat->Parent;
     }
     if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentDiceProp.MatNum))
     {
         PropIn.MatNum = Mat->Parent;
     }
 }