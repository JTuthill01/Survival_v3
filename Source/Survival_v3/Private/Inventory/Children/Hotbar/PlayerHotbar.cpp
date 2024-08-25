#include "Inventory/Children/Hotbar/PlayerHotbar.h"
#include "DataAssets/Primairy/ItemInfo.h"

UPlayerHotbar::UPlayerHotbar() : CurrentType(EItemType::EIT_Resource)
{
}

bool UPlayerHotbar::CheckHotBar(const int32 Index, EItemType& OutType)
{
	if (Items[Index].ItemID == 0)
		return false;

	if (auto&& Item = Items[Index].ItemAsset.LoadSynchronous(); IsValid(Item))
	{
		OutType = Item->ItemType;

		return true;
	}
	
	return false;
}

