#include "DataAssets/Primairy/ItemInfo.h"

UItemInfo::UItemInfo() : ItemID(0), ItemDamage(0), StackSize(0), ItemCurrentHP(0), ItemMaxHP(0), CurrentAmmo(0), MaxAmmo(0), ItemWeight(0.0), ItemIcon(nullptr), ItemClassRef(nullptr),
	ItemName(FText()), ItemDescription(FText()), ItemRarity(EItemRarity::EIR_Common), ItemType(EItemType::EIT_Resource), ArmourType(EArmourType::EAT_Helmet), bIsStackable(false), bDoesUseAmmo(false)
{
}
