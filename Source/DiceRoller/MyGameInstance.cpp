// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Engine/ObjectLibrary.h"

UMyGameInstance::UMyGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance Constructor"));
	CurrentMeshStyle = MeshStyle::Default;
	PreviewMeshStyle = MeshStyle::Default;
	PreviewDiceType = DiceType::D6;	
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance Init"));

	// Create dynamic material instances
	PreviewDynMatDiceFace = UMaterialInstanceDynamic::Create(CurrentMatDiceFace, this);
	PreviewDynMatDiceNum = UMaterialInstanceDynamic::Create(CurrentMatDiceNum, this);
	PreviewDynMatTray = UMaterialInstanceDynamic::Create(CurrentMatTray, this);
	
}

