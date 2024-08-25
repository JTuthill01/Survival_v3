#pragma once

#include "HarvestingInfo.generated.h"

UENUM(BlueprintType)
enum class EHarvestingToolType : uint8 { EHTT_Pickaxe, EHTT_Hatchet };

UENUM(BlueprintType)
enum class EToolTier : uint8 { ETT_Stone, ETT_Iron };

USTRUCT(BlueprintType)
struct FResourceStructure
{
	GENERATED_BODY()

	FResourceStructure() : Resource(nullptr), Quantity(0), PreferredTool(EHarvestingToolType::EHTT_Pickaxe)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<class UItemInfo> Resource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Quantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EHarvestingToolType PreferredTool;
};