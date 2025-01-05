#pragma once

#include "CraftingStruct.generated.h"

USTRUCT(BlueprintType)
struct FCraftingStruct
{
	GENERATED_BODY()
	
	FCraftingStruct() : Index(NULL), Quantity(NULL), ItemID(NULL)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Index;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Quantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID;
};