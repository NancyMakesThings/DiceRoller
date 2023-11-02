#pragma once

#include "CoreMinimal.h"
#include "DiceType.generated.h"

UENUM(BlueprintType)
enum class DiceType : uint8
{
	D4,
	D6,
	D8,
	D10,
	D12,
	D20,
	D100	
};
