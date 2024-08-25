#pragma once

#include "ItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemsStruct
{
	GENERATED_BODY()
	
	FItemsStruct() = default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemQuantity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemDamage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentHP = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxHP = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentAmmo = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxAmmo = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 StackSize = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<class UItemInfo> ItemAsset = nullptr;
};