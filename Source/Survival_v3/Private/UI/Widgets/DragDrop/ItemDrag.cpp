#include "UI/Widgets/DragDrop/ItemDrag.h"

UItemDrag::UItemDrag() : SlotIndex(0), FromContainer(EContainerType::ECT_Inventory), ItemType(EItemType::EIT_Resource), ArmorType(EArmourType::EAT_Helmet)
{
}

void UItemDrag::GetItemDragInfo_Implementation(int32& OutIndex, EContainerType& Container, EArmourType& OutArmorType, EItemType& OutItemType)
{
	OutIndex = SlotIndex;

	Container = FromContainer;

	OutArmorType = ArmorType;

	OutItemType = ItemType;
}

void UItemDrag::SetItemDragVariables(const int32 InIndex, const EContainerType InContainer, const EItemType InType, const EArmourType InArmor)
{
	SlotIndex = InIndex;

	FromContainer = InContainer;

	ItemType = InType;

	ArmorType = InArmor;
}
