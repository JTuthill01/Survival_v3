#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/ItemRarity/ItemRarity.h"
#include "Enums/ItemType/ItemType.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "ItemInfo.generated.h"

UCLASS()
class SURVIVAL_V3_API UItemInfo : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UItemInfo();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	int32 ItemDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	int32 StackSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	int32 ItemCurrentHP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	int32 ItemMaxHP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	double ItemWeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	TSoftClassPtr<class AItemMaster> ItemClassRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	EItemRarity ItemRarity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	EArmourType ArmourType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	bool bIsStackable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	bool bDoesUseAmmo;
};
