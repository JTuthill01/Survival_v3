#include "UI/Widgets/Crafting/CraftingSlot/CraftingSlot.h"

UCraftingSlot::UCraftingSlot(const FObjectInitializer& Object) : Super(Object), bCanCraftItem(false), ItemID(0), ItemIndex(0), ContainerType(EContainerType::ECT_Inventory),
	CraftingType(ECraftingType::ECT_PlayerInventory), ItemName(FText())
{
}
