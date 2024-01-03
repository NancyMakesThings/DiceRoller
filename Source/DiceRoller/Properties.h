#pragma once

#include "CoreMinimal.h"
#include "MeshStyle.h"
#include "Properties.generated.h"

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
	UMaterialInterface* MatFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	UMaterialInterface* MatNum;


	// Color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	FLinearColor ColorFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	FLinearColor ColorNum;

};

USTRUCT(BlueprintType)
struct FTrayProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	UMaterialInterface* Mat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Properties")
	FLinearColor Color;
};
