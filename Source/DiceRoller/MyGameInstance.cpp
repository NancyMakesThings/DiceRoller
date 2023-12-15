// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance Init, set up current dynamic materials"));
    
	CurrentProp.MatDiceFace = UMaterialInstanceDynamic::Create(CurrentProp.MatDiceFace, this);
	CurrentProp.MatDiceNum = UMaterialInstanceDynamic::Create(CurrentProp.MatDiceNum, this);
	CurrentProp.MatTray = UMaterialInstanceDynamic::Create(CurrentProp.MatTray, this);

    if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentProp.MatDiceFace))
    {
        CurrentProp.ColorDiceFace = Mat->K2_GetVectorParameterValue("BaseColor");
    }

    if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentProp.MatDiceNum))
    {
        CurrentProp.ColorDiceNum = Mat->K2_GetVectorParameterValue("BaseColor");
    }

    if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(CurrentProp.MatTray))
    {
        CurrentProp.ColorTray = Mat->K2_GetVectorParameterValue("BaseColor");
    }
    
}
