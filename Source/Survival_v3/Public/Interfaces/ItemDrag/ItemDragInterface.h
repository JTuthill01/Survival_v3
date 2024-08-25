#pragma once

#include "CoreMinimal.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "Enums/ItemType/ItemType.h"
#include "UObject/Interface.h"
#include "ItemDragInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemDragInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_V3_API IItemDragInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void GetItemDragInfo(int32& OutIndex, EContainerType& Container, EArmourType& OutArmorType, EItemType& OutItemType);
};
