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

    // Get material assets
    
    GetAssetData(AssetDataMatDiceFace, NamesMatDiceFace, "/Game/DiceRoller/Core/Dice/Materials/Face");
	
}

void UMyGameInstance::GetAssetData(TArray<FAssetData> &AssetDatas, TArray<FString> &Names, const FString &Path)
{
    UE_LOG(LogTemp, Warning, TEXT("MyGameInstance GetAssetData"));

    UObjectLibrary* ObjectLibrary;
    ObjectLibrary = UObjectLibrary::CreateLibrary(UMaterialInstance::StaticClass(), true, true);
    //ObjectLibrary->AddToRoot();
    //ObjectLibrary->LoadAssetDataFromPath("/Game/DiceRoller/Core/Dice");
    ObjectLibrary->LoadAssetDataFromPath(Path);
    ObjectLibrary->GetAssetDataList(AssetDatas);

    UE_LOG(LogTemp, Warning, TEXT("MyGameInstance Post GetAssetDataList"));

    for (FAssetData& AssetData : AssetDatas)
    {
        FString SplitOn = "_";
        FString Left, Right;
        AssetData.AssetName.ToString().Split(SplitOn, &Left, &Right);
        Names.Add(Right);

        UE_LOG(LogTemp, Warning, TEXT("Asset: %s"), *Right);
    }

}

TArray<FString> UMyGameInstance::GetNamesMatDiceFace() const
{
    return NamesMatDiceFace;
}
