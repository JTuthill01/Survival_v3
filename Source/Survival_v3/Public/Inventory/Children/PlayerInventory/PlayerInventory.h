#pragma once

#include "CoreMinimal.h"
#include "Inventory/Master/ItemsContainerMaster.h"
#include "PlayerInventory.generated.h"

UCLASS()
class SURVIVAL_V3_API UPlayerInventory : public UItemsContainerMaster
{
	GENERATED_BODY()

public:
	UPlayerInventory();

	virtual void HandleSlotDrop(const TObjectPtr<UItemsContainerMaster> FromContainer, const int32 FromIndex, const int32 DroppedIndex) override;

	virtual bool AddItemsToIndex(const FItemsStruct& ItemInfo, const int32 LocalSpecificIndex, const int32 LocalItemIndex) override;

	virtual bool RemoveItemAtIndex(const int32 IndexToRemove) override;
};
