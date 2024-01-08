// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Properties.h"
#include "MyGameInstance.generated.h"

// Forward declarations
class APreview;
class UObjectLibrary;
class UMySaveGame;

/**
 * Custom subclass of GameInstance. 
 * Handles material and mesh selections (persistent throughout game instance)
 */

UCLASS()
class DICEROLLER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	virtual void Init() override;

	virtual void Shutdown() override;

protected: 

	UPROPERTY(BlueprintReadOnly, Category = "Save")
	UMySaveGame* CurrentSave;

	UPROPERTY(BlueprintReadOnly, Category = "Save")
	FString SaveName = "UserPresets";

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
		FDiceProperties CurrentDiceProp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tray Properties")
		FTrayProperties CurrentTrayProp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
		TArray<FDiceProperties> CurrentPresets;

	// Setters and getters for protected variables
	UFUNCTION(BlueprintCallable)
	FDiceProperties GetCurrentDiceProp() const;
	
	UFUNCTION(BlueprintCallable)
	FTrayProperties GetCurrentTrayProp() const;

	UFUNCTION(BlueprintCallable)
	void UpdateCurrentDiceProp(const FDiceProperties & NewProp);

	UFUNCTION(BlueprintCallable)
	void UpdateCurrentTrayProp(const FTrayProperties & NewProp);

	UFUNCTION(BlueprintCallable)
	void UpdatePreset(const FDiceProperties & NewProp, int Index);

	UFUNCTION(BlueprintCallable)
	bool LoadSave();

	UFUNCTION(BlueprintCallable)
	void WriteSave();

	UFUNCTION(BlueprintCallable)
	void CreateDynMatFromCurrent(bool PreviousSaveExists);

	UFUNCTION(BlueprintCallable)
	void SetDicePropSafe(FDiceProperties & PropIn);
};
