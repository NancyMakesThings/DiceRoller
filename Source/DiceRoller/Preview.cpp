// Fill out your copyright notice in the Description page of Project Settings.


#include "Preview.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "MyGameInstance.h"
#include "Engine/ObjectLibrary.h"
#include "Properties.h"
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
    UpdateDiceProp();
    UpdateTrayProp();

    MeshDice->SetMaterial(0, DiceProp.MatFace);
    MeshDice->SetMaterial(1, DiceProp.MatNum);
    MeshTray->SetMaterial(0, TrayProp.Mat);

    // Get material assets
    GetAssetData(AssetDataDiceMatFace, NamesDiceMatFace, "/Game/DiceRoller/Core/Dice/Materials/Face");
    GetAssetData(AssetDataDiceMatNum, NamesDiceMatNum, "/Game/DiceRoller/Core/Dice/Materials/Number");
    GetAssetData(AssetDataTrayMat, NamesTrayMat, "/Game/DiceRoller/Core/Tray/Materials/Face");

    // Set up scene capture components
    SceneCaptureDice->ShowOnlyComponent(MeshDice);
    SceneCaptureTray->ShowOnlyComponent(MeshTray);
    
}

// Called every frame
void APreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APreview::UpdateDiceProp()
{
    if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
    {
        DiceProp.MeshStyle = Game->GetCurrentDiceProp().MeshStyle;

        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(Game->GetCurrentDiceProp().MatFace))
        {
            DiceProp.MatFace = UMaterialInstanceDynamic::Create(Mat->Parent, this);
            DiceProp.ColorFace = Game->GetCurrentDiceProp().ColorFace;
        }

        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(Game->GetCurrentDiceProp().MatNum))
        {
            DiceProp.MatNum = UMaterialInstanceDynamic::Create(Mat->Parent, this);
            DiceProp.ColorNum = Game->GetCurrentDiceProp().ColorNum;
        }
    }
}

void APreview::UpdateTrayProp()
{
    if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
    {
        if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(Game->GetCurrentTrayProp().Mat))
        {
            UE_LOG(LogTemp, Warning, TEXT("APreview UpdateTrayProp"));
            TrayProp.Mat = UMaterialInstanceDynamic::Create(Mat->Parent, this);
            TrayProp.Color = Game->GetCurrentTrayProp().Color;
        }
    }
}

void APreview::UpdateMeshStyle(MeshStyle MeshName, UStaticMesh* NewMesh)
{
    DiceProp.MeshStyle = MeshName;
    MeshDice->SetStaticMesh(NewMesh);
}

void APreview::UpdateDiceMatFace(UMaterialInterface* NewMat)
{
    UE_LOG(LogTemp, Warning, TEXT("APreview UpdateDiceFaceMat"));

    // Set preview materials to dynamic materials
    DiceProp.MatFace = NewMat;

    if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
    {
        MeshDice->SetMaterial(0, DiceProp.MatFace);
    }

    UpdateDiceColorFace(DiceProp.ColorFace);

}

void APreview::UpdateDiceMatNum(UMaterialInterface* NewMat)
{
    // Set preview materials to dynamic materials
    DiceProp.MatNum = NewMat;

    if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
    {
        MeshDice->SetMaterial(1, DiceProp.MatNum);
    }

    UpdateDiceColorNum(DiceProp.ColorNum);
}

void APreview::UpdateDiceColorFace(const FLinearColor & Color)
{
    DiceProp.ColorFace = Color;
    if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(DiceProp.MatFace))
    {
        Mat->SetVectorParameterValue("BaseColor", Color);
        Mat->SetVectorParameterValue("DiffuseColor", Color); // account for differences in naming for different materials
    }
}

void APreview::UpdateDiceColorNum(const FLinearColor & Color)
{
    DiceProp.ColorNum = Color;
    if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(DiceProp.MatNum))
    {
        Mat->SetVectorParameterValue("BaseColor", Color);
    }
}

void APreview::UpdateTrayMat(UMaterialInterface* NewMat)
{
    // Set preview materials to dynamic materials
    TrayProp.Mat = NewMat;

    if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
    {
        MeshTray->SetMaterial(0, TrayProp.Mat);
    }

    UpdateTrayColor(TrayProp.Color);
}

void APreview::UpdateTrayColor(const FLinearColor& Color)
{
    TrayProp.Color = Color;
    if (UMaterialInstanceDynamic* Mat = Cast<UMaterialInstanceDynamic>(TrayProp.Mat))
    {
        UE_LOG(LogTemp, Warning, TEXT("APreview UpdateTrayColor"));
        Mat->SetVectorParameterValue("BaseColor", Color);
    }
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
