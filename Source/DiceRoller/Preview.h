// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiceProperties.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	FDiceProperties PreviewProp;

	// Preview dice type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	DiceType DiceType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	// Update mesh
	UFUNCTION(BlueprintCallable)
	void UpdatePreviewProp();

	UFUNCTION(BlueprintCallable)
	void UpdateMeshStyle(MeshStyle MeshName, UStaticMesh* NewMesh);

	UFUNCTION(BlueprintCallable)
	void UpdateColorDiceFace(const FLinearColor & Color);

	UFUNCTION(BlueprintCallable)
	void UpdateColorDiceNum(const FLinearColor & Color);

	UFUNCTION(BlueprintCallable)
	void UpdateColorTray(const FLinearColor& Color);

	UFUNCTION(BlueprintCallable)
	void UpdateMatDiceFace(UMaterialInterface* NewMat);

	UFUNCTION(BlueprintCallable)
	void UpdateMatDiceNum(UMaterialInterface* NewMat);

	UFUNCTION(BlueprintCallable)
	void UpdateMatTray(UMaterialInterface* NewMat);

	// Materials library handling
	UFUNCTION(BlueprintCallable)
	void GetAssetData(TArray<FAssetData>& AssetDatas, TArray<FString>& StringDatas, const FString& Path);

	UPROPERTY(BlueprintReadOnly)
	TArray<FAssetData> AssetDataMatDiceFace;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	TArray<FString> NamesMatDiceFace;

	UPROPERTY(BlueprintReadOnly)
	TArray<FAssetData> AssetDataMatDiceNum;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	TArray<FString> NamesMatDiceNum;

	UPROPERTY(BlueprintReadOnly)
	TArray<FAssetData> AssetDataMatTray;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Preview")
	TArray<FString> NamesMatTray;

protected:


};
