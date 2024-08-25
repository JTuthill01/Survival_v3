#pragma once

UENUM(BlueprintType)
enum class EArmourType : uint8 { EAT_Helmet, EAT_Chest, EAT_Pants, EAT_Boots, EAT_BackPack };

UENUM(BlueprintType)
enum class EContainerType : uint8 { ECT_Inventory, ECT_HotBar, ECT_Storage, ECT_Armour };