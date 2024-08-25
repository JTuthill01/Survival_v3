#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Interfaces/ItemDrag/ItemDragInterface.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "Enums/ItemType/ItemType.h"
#include "ItemDrag.generated.h"

UCLASS()
class SURVIVAL_V3_API UItemDrag : public UDragDropOperation, public IItemDragInterface
{
	GENERATED_BODY()

public:
	UItemDrag();

	virtual void GetItemDragInfo_Implementation(int32& OutIndex, EContainerType& Container, EArmourType& OutArmorType, EItemType& OutItemType) override;

	void SetItemDragVariables(const int32 InIndex, const EContainerType InContainer, const EItemType InType, const EArmourType InArmor);

#pragma region Variables
	int32 SlotIndex;

	EContainerType FromContainer;

	EItemType ItemType;

	EArmourType ArmorType;
#pragma endregion
};
