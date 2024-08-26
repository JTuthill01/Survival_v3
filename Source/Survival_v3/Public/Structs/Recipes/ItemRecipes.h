#pragma once

#include "ItemRecipes.generated.h"

USTRUCT(BlueprintType)
struct FItemRecipeInfo
{
	GENERATED_BODY()

	FItemRecipeInfo() : ItemID(0), CurrentQuantity(0), NeededQuantity(0), ItemName(FText()), ItemIcon(nullptr)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentQuantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 NeededQuantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ItemIcon;
};

UENUM(BlueprintType)
enum class ECraftingType : uint8 { ECT_PlayerInventory, ECT_CookingPot, ECT_CraftingBench, ECT_SmeltingForge, ECT_AdvancedWorkbench, ECT_StorageBox, ECT_CropPlot };