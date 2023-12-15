// Fill out your copyright notice in the Description page of Project Settings.


#include "Preview.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "MyGameInstance.h"
#include "Engine/ObjectLibrary.h"
#include "DiceProperties.h"
#include "Dice.h"

// Sets default values
APreview::APreview()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create components
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    SceneCaptureDice = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureDice"));
    SceneCaptureTray = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureTray"));
    SpringArmDice = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmDice"));
    SpringArmTray = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmTray"));
    MeshDice = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshDice"));
    MeshTray = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshTray"));

    // Attach components
    MeshDice->SetupAttachment(RootComponent);
    MeshTray->SetupAttachment(RootComponent);
    SpringArmDice->SetupAttachment(RootComponent);
    SpringArmTray->SetupAttachment(RootComponent);
    SceneCaptureDice->SetupAttachment(SpringArmDice, USpringArmComponent::SocketName);
    SceneCaptureTray->SetupAttachment(SpringArmTray, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APreview::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Preview BeginPlay, set up dynamic materials"));

    // Create dynamic material instances and set preview materials to dynamic materials
    UpdatePreviewProp();

    MeshDice->SetMaterial(0, PreviewProp.MatDiceFace);
    MeshDice->SetMaterial(1, PreviewProp.MatDiceNum);
    MeshTray->SetMaterial(0, PreviewProp.MatTray);

    // Get material assets
    GetAssetData(AssetDataMatDiceFace, NamesMatDiceFace, "/Game/DiceRoller/Core/Dice/Materials/Face");
    GetAssetData(AssetDataMatDiceNum, NamesMatDiceNum, "/Game/DiceRoller/Core/Dice/Materials/Number");
    GetAssetData(AssetDataMatTray, NamesMatTray, "/Game/DiceRoller/Core/Tray/Materials/Face");

    // Set up scene capture components
    SceneCaptureDice->ShowOnlyComponent(MeshDice);
    SceneCaptureTray->ShowOnlyComponent(MeshTray);
    
}

// Called every frame
void APreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APreview::UpdatePreviewProp()
{
    if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
    {
        PreviewProp.MeshStyle = Game->CurrentProp.MeshStyle;

        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(Game->CurrentProp.MatDiceFace))
        {
            PreviewProp.MatDiceFace = UMaterialInstanceDynamic::Create(Mat->Parent, this);
            PreviewProp.ColorDiceFace = Game->CurrentProp.ColorDiceFace;
        }

        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(Game->CurrentProp.MatDiceNum))
        {
            PreviewProp.MatDiceNum = UMaterialInstanceDynamic::Create(Mat->Parent, this);
            PreviewProp.ColorDiceNum = Game->CurrentProp.ColorDiceNum;
        }

        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(Game->CurrentProp.MatTray))
        {
            PreviewProp.MatTray = UMaterialInstanceDynamic::Create(Mat->Parent, this);
            PreviewProp.ColorTray = Game->CurrentProp.ColorTray;
        }

    }

}

void APreview::UpdateMeshStyle(MeshStyle MeshName, UStaticMesh* NewMesh)
{
    PreviewProp.MeshStyle = MeshName;
    MeshDice->SetStaticMesh(NewMesh);
}

void APreview::UpdateColorDiceFace(const FLinearColor & Color)
{
    PreviewProp.ColorDiceFace = Color;
    if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(PreviewProp.MatDiceFace))
    {
        Mat->SetVectorParameterValue("BaseColor", Color);
        Mat->SetVectorParameterValue("DiffuseColor", Color); // account for differences in naming for different materials
    }
}

void APreview::UpdateColorDiceNum(const FLinearColor & Color)
{
    PreviewProp.ColorDiceNum = Color;
    if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(PreviewProp.MatDiceNum))
    {
        Mat->SetVectorParameterValue("BaseColor", Color);
    }
}

void APreview::UpdateColorTray(const FLinearColor& Color)
{
    PreviewProp.ColorTray = Color;
    if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(PreviewProp.MatTray))
    {
        Mat->SetVectorParameterValue("BaseColor", Color);
    }
}

void APreview::UpdateMatDiceFace(UMaterialInterface* NewMat)
{
    UE_LOG(LogTemp, Warning, TEXT("APreview UpdateDiceFaceMat"));

    // Set preview materials to dynamic materials
    PreviewProp.MatDiceFace = NewMat;
    
    if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
    {
        MeshDice->SetMaterial(0, PreviewProp.MatDiceFace);
    }
    

    UpdateColorDiceFace(PreviewProp.ColorDiceFace);

}

void APreview::UpdateMatDiceNum(UMaterialInterface* NewMat)
{
    // Set preview materials to dynamic materials
    PreviewProp.MatDiceNum = NewMat;

    if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
    {
        MeshDice->SetMaterial(1, PreviewProp.MatDiceNum);
    }

    UpdateColorDiceNum(PreviewProp.ColorDiceNum);
}

void APreview::UpdateMatTray(UMaterialInterface* NewMat)
{
    // Set preview materials to dynamic materials
    PreviewProp.MatTray = NewMat;

    if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
    {
        MeshTray->SetMaterial(0, PreviewProp.MatTray);
    }

    UpdateColorTray(PreviewProp.ColorTray);
}

void APreview::GetAssetData(TArray<FAssetData>& AssetDatas, TArray<FString>& Names, const FString& Path)
{
    UE_LOG(LogTemp, Warning, TEXT("APreview GetAssetData"));

    UObjectLibrary* ObjectLibrary;
    ObjectLibrary = UObjectLibrary::CreateLibrary(UMaterialInstance::StaticClass(), true, true);
    //ObjectLibrary->AddToRoot();
    //ObjectLibrary->LoadAssetDataFromPath("/Game/DiceRoller/Core/Dice");
    ObjectLibrary->LoadAssetDataFromPath(Path);
    ObjectLibrary->GetAssetDataList(AssetDatas);

    UE_LOG(LogTemp, Warning, TEXT("APreview Post GetAssetDataList"));

    for (FAssetData& AssetData : AssetDatas)
    {
        FString Left, Right;
        AssetData.AssetName.ToString().Split(TEXT("_"), &Left, &Right);
        Names.Add(Right);

        UE_LOG(LogTemp, Warning, TEXT("Asset: %s"), *Right);
    }

}
