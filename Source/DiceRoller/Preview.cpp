// Fill out your copyright notice in the Description page of Project Settings.


#include "Preview.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "MyGameInstance.h"

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

    // Set up scene capture components
    SceneCaptureDice->ShowOnlyComponent(MeshDice);
    SceneCaptureTray->ShowOnlyComponent(MeshTray);

    // Set preview materials to dynamic materials
    if (UMyGameInstance* Game = CastChecked<UMyGameInstance>(GetGameInstance()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Preview BeginPlay, set up dynamic materials"));

        MeshDice->SetMaterial(0, Game->PreviewDynMatDiceFace);
        MeshDice->SetMaterial(1,Game->PreviewDynMatDiceNum);
        MeshTray->SetMaterial(0, Game->PreviewDynMatTray);
    }
    
}

// Called every frame
void APreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APreview::UpdateDiceMesh(UStaticMesh* NewMesh)
{
    MeshDice->SetStaticMesh(NewMesh);
}

