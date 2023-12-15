#pragma once

#include "CoreMinimal.h"
#include "MeshStyle.h"
#include "DiceProperties.generated.h"

// Handle dice properties
USTRUCT(BlueprintType)
struct FDiceProperties
{
	GENERATED_USTRUCT_BODY()


	// Mesh style
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	MeshStyle MeshStyle;

	// Materials
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	UMaterialInterface* MatDiceFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	UMaterialInterface* MatDiceNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	UMaterialInterface* MatTray;

	// Color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	FLinearColor ColorDiceFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	FLinearColor ColorDiceNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	FLinearColor ColorTray;
};

