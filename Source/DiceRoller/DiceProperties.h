#pragma once

#include "CoreMinimal.h"
#include "MeshStyle.h"
#include "DiceProperties.generated.h"

// Handle dice properties
USTRUCT(BlueprintType)
struct FDiceProperties
{
	GENERATED_USTRUCT_BODY()

	// Materials
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	UMaterialInterface* MatDiceFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	UMaterialInterface* MatDiceNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	UMaterialInterface* MatTray;

	// Mesh style
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	MeshStyle MeshStyle;

	// Color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	FVector ColorDiceFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	FVector ColorDiceNum;

};

