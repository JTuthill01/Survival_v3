#include "Inventory/Children/PlayerInventory/PlayerInventory.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Interfaces/Character/Controller/PlayerControllerInterface.h"
#include "Kismet/GameplayStatics.h"

UPlayerInventory::UPlayerInventory()
{
}

void UPlayerInventory::HandleSlotDrop(const TObjectPtr<UItemsContainerMaster> FromContainer, const int32 FromIndex, const int32 DroppedIndex)
{
	//FromContainer = LocalFromContainer
	//FromIndex = LocalFromIndex
	//DroppedIndex = LocalDroppedIndex

	if (FromContainer == this && FromIndex == DroppedIndex)
		return;

	switch (FromContainer->ContainerType)
	{
	case EContainerType::ECT_Inventory:

		FromContainer->TransferItem(this, DroppedIndex, FromIndex);
			
		break;
			
	case EContainerType::ECT_HotBar:

		FromContainer->TransferItem(this, DroppedIndex, FromIndex);
			
		break;
			
	case EContainerType::ECT_Storage:

		FromContainer->TransferItem(this, DroppedIndex, FromIndex);
			
		break;
			
	case EContainerType::ECT_Armour:
		break;

	default:
		break;
	}
	
}

bool UPlayerInventory::AddItemsToIndex(const FItemsStruct& ItemInfo, const int32 LocalSpecificIndex, const int32 LocalItemIndex)
{
	const bool& bIsSuccessful = Super::AddItemsToIndex(ItemInfo, LocalSpecificIndex, LocalItemIndex);

	if (const TObjectPtr<APlayerCharacter> PlayerRef = IPlayerCharacterInterface::Execute_GetPlayerRef(GetOwner()); IsValid(PlayerRef))
	{
		IPlayerCharacterInterface::Execute_UpdateItem(PlayerRef, ContainerType, LocalSpecificIndex, GetItemAtIndex(LocalSpecificIndex));

		return bIsSuccessful;
	}

	return false;
}

bool UPlayerInventory::RemoveItemAtIndex(const int32 IndexToRemove)
{
	const bool& bIsSuccessful = Super::RemoveItemAtIndex(IndexToRemove);

	if (const TObjectPtr<APlayerCharacterController> PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); IsValid(PC))
	{
		IPlayerControllerInterface::Execute_ResetItemSlot(PC, ContainerType, IndexToRemove);

		return bIsSuccessful;
	}

	return false;
}
