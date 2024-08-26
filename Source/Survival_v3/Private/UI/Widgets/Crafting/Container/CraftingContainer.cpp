#include "UI/Widgets/Crafting/Container/CraftingContainer.h"
#include "Character/Player/PlayerCharacter.h"

UCraftingContainer::UCraftingContainer(const FObjectInitializer& Object) : Super(Object), ContainerType(EContainerType::ECT_Inventory), CraftingType(ECraftingType::ECT_PlayerInventory)
{
}

void UCraftingContainer::InitSlots()
{
	if (const TObjectPtr<APlayerCharacter> PlayerRef = IPlayerCharacterInterface::Execute_GetPlayerRef(GetOwningPlayerPawn()); IsValid(PlayerRef))
		IPlayerCharacterInterface::Execute_GetEndGramsAndItems(PlayerRef, CraftingType);
}
