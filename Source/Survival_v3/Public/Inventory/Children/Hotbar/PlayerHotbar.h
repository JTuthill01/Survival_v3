#pragma once

#include "CoreMinimal.h"
#include "Enums/ItemType/ItemType.h"
#include "Inventory/Master/ItemsContainerMaster.h"
#include "PlayerHotbar.generated.h"

UCLASS()
class SURVIVAL_V3_API UPlayerHotbar : public UItemsContainerMaster
{
	GENERATED_BODY()

public:
	UPlayerHotbar();

	bool CheckHotBar(const int32 Index, EItemType& OutType);
	
	EItemType CurrentType;
};
