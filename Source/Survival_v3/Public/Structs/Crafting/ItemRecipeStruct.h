#pragma once

#include "ItemRecipeStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemRecipeStruct
{
	GENERATED_BODY()

	FItemRecipeStruct() : ItemID(0), ItemQuantity(0), ItemName(FText()), ItemIcon(nullptr)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemQuantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ItemIcon;
};