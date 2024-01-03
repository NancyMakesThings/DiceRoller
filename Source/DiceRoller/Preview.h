// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Properties.h"
#include "DiceType.h"
#include "Preview.generated.h"

// Forward declarations
class USceneCaptureComponent2D;
class USpringArmComponent;


UCLASS()
class DICEROLLER_API APreview : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APreview();

	// Preview dice type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	DiceType DiceType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Properties
	UPROPERTY(BlueprintReadOnly, Category = "Dice Properties")
	FDiceProperties DiceProp;

	UPROPERTY(BlueprintReadOnly, Category = "Tray Properties")
	FTrayProperties TrayProp;

	// Materials library
	UPROPERTY(BlueprintReadOnly)
	TArray<FAssetData> AssetDataDiceMatFace;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	TArray<FString> NamesDiceMatFace;

	UPROPERTY(BlueprintReadOnly)
	TArray<FAssetData> AssetDataDiceMatNum;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	TArray<FString> NamesDiceMatNum;

	UPROPERTY(BlueprintReadOnly)
	TArray<FAssetData> AssetDataTrayMat;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	TArray<FString> NamesTrayMat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Scene capture components
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	USceneCaptureComponent2D* SceneCaptureTray;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	USceneCaptureComponent2D* SceneCaptureDice;

	// Spring arm components
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	USpringArmComponent* SpringArmTray;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	USpringArmComponent* SpringArmDice;

	// Static mesh components
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	UStaticMeshComponent* MeshTray;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	UStaticMeshComponent* MeshDice;

	// Update mesh to match current
	UFUNCTION(BlueprintCallable)
	void UpdateDiceProp();

	UFUNCTION(BlueprintCallable)
	void UpdateTrayProp();

	// Update properties
	UFUNCTION(BlueprintCallable)
	void UpdateMeshStyle(MeshStyle MeshName, UStaticMesh* NewMesh);

	UFUNCTION(BlueprintCallable)
	void UpdateDiceMatFace(UMaterialInterface* NewMat);

	UFUNCTION(BlueprintCallable)
	void UpdateDiceMatNum(UMaterialInterface* NewMat);

	UFUNCTION(BlueprintCallable)
	void UpdateDiceColorFace(const FLinearColor & Color);

	UFUNCTION(BlueprintCallable)
	void UpdateDiceColorNum(const FLinearColor & Color);

	UFUNCTION(BlueprintCallable)
	void UpdateTrayMat(UMaterialInterface* NewMat);

	UFUNCTION(BlueprintCallable)
	void UpdateTrayColor(const FLinearColor& Color);

	// Materials library handling
	UFUNCTION(BlueprintCallable)
	void GetAssetData(TArray<FAssetData>& AssetDatas, TArray<FString>& StringDatas, const FString& Path);
};
