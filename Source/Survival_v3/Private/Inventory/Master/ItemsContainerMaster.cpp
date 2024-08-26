#include "Inventory/Master/ItemsContainerMaster.h"
#include "Character/Player/PlayerCharacter.h"
#include "DataAssets/Primairy/ItemInfo.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UItemsContainerMaster::UItemsContainerMaster() : ContainerType(EContainerType::ECT_Inventory)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UItemsContainerMaster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UItemsContainerMaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UItemsContainerMaster::FindEmptySlot(int32& LocalEmptySlotIndex, bool& bFoundEmptySlot)
{
	for (int32 i = 0; i < Items.Num(); ++i)
	{
		if (Items[i].ItemID == 0)
		{
			LocalEmptySlotIndex = i; 

			bFoundEmptySlot = true;

			break;
		}
	}
}

void UItemsContainerMaster::AddItem(FItemsStruct Item, bool AddSplitItem)
{
	FItemsStruct& LocalItemInfo = Item;

	if (const TSoftObjectPtr<UItemInfo> LoadedInfo = Item.ItemAsset.LoadSynchronous())
	{
		int32 LocalEmptyIndex;
		
		if (LoadedInfo->bIsStackable)
		{
			if (!AddSplitItem)
			{
				int32 TotalItemQuantity;
				int32 MaxStackSize;
				int32 CurrentSlotQuantity;
				int32 TempSlotQuantity;
				
				if(HasItemsToStack(LocalItemInfo))
				{
					for (int32 i = 0; i < Items.Num(); ++i)
					{
						if (LocalItemInfo.ItemID == Items[i].ItemID && Items[i].ItemQuantity < Items[i].StackSize)
						{
							TotalItemQuantity = LocalItemInfo.ItemQuantity;
							MaxStackSize = Items[i].StackSize;
							LocalEmptyIndex = i;
							CurrentSlotQuantity = Items[i].ItemQuantity;
							
							TempSlotQuantity = CurrentSlotQuantity;

							CurrentSlotQuantity = SetCurrentSlotQuantity(CurrentSlotQuantity, TotalItemQuantity, MaxStackSize);

							LocalItemInfo.ItemQuantity = CurrentSlotQuantity;

							Items[LocalEmptyIndex] = LocalItemInfo;

							UpdateUI(LocalEmptyIndex, LocalItemInfo);

							TotalItemQuantity = SetTotalItem(TotalItemQuantity, TempSlotQuantity, MaxStackSize, CurrentSlotQuantity);

							LocalItemInfo.ItemQuantity = TotalItemQuantity;
						}
					}
				}

				else if (LocalItemInfo.ItemQuantity > 0 || LocalItemInfo.ItemQuantity > LocalItemInfo.StackSize)
				{
					TotalItemQuantity = LocalItemInfo.ItemQuantity;
					MaxStackSize = LocalItemInfo.StackSize;

					bool bWasSlotFound;
					
					FindEmptySlot(LocalEmptyIndex, bWasSlotFound);

					if (bWasSlotFound)
					{
						CurrentSlotQuantity = NULL;

						TempSlotQuantity = NULL;

						CurrentSlotQuantity = SetSlotQuantity(CurrentSlotQuantity, TotalItemQuantity, MaxStackSize);

						LocalItemInfo.ItemQuantity = CurrentSlotQuantity;

						Items[LocalEmptyIndex] = LocalItemInfo;

						UpdateUI(LocalEmptyIndex, LocalItemInfo);

						if (TotalItemQuantity = CalcTotalItemQuantity(TempSlotQuantity, TotalItemQuantity, MaxStackSize, CurrentSlotQuantity); TotalItemQuantity > 0)
						{
							TotalItemQuantity = LocalItemInfo.ItemQuantity;
							MaxStackSize = LocalItemInfo.StackSize;
							
							FindEmptySlot(LocalEmptyIndex, bWasSlotFound);

							if (bWasSlotFound)
							{
								CurrentSlotQuantity = NULL;

								TempSlotQuantity = NULL;

								CurrentSlotQuantity = SetSlotQuantity(CurrentSlotQuantity, TotalItemQuantity, MaxStackSize);

								LocalItemInfo.ItemQuantity = CurrentSlotQuantity;

								Items[LocalEmptyIndex] = LocalItemInfo;

								UpdateUI(LocalEmptyIndex, LocalItemInfo);
							}
						}
					}
				}
			}
		}

		else if (!LoadedInfo->bIsStackable || AddSplitItem || LocalItemInfo.ItemQuantity > 0 || LocalItemInfo.ItemQuantity > LocalItemInfo.StackSize)
		{
			bool bIsEmpty;

			FindEmptySlot(LocalEmptyIndex, bIsEmpty);

			if (bIsEmpty)
			{
				Items[LocalEmptyIndex] = LocalItemInfo;

				UpdateUI(LocalEmptyIndex, LocalItemInfo);
			}
		}
	}
}

void UItemsContainerMaster::TransferItem(const TObjectPtr<UItemsContainerMaster>& ToComponent, const int32 ToIndex, const int32 ItemIndexToTransfer)
{
	//ToComponent = LocalReceiverComponent
	//ToIndex = LocalToIndex
	//ItemIndexToTransfer = LocalItemIndex
	
	if (IsSlotEmpty(ItemIndexToTransfer) || ToIndex == ItemIndexToTransfer && ToComponent == this)
		return;

	if (IsValid(ToComponent))
	{
		if (const FItemsStruct& LocalItemToTransfer = GetItemAtIndex(ItemIndexToTransfer); ToComponent->AddItemsToIndex(LocalItemToTransfer, ToIndex, ItemIndexToTransfer))
			RemoveItemAtIndex(ItemIndexToTransfer);
	}
}

TArray<FSimpleItemStruct> UItemsContainerMaster::GetItemQuantities()
{
	TArray<FSimpleItemStruct> LocalItemArray;

	bool bFoundItem = false;
	
	for (int32 i = 0; i < Items.Num(); ++i)
	{
		if (Items[i].ItemID != 0)
		{
			for (int32 j = 0; j < LocalItemArray.Num(); ++j)
			{
				if (LocalItemArray[j].ItemID == Items[i].ItemID)
				{
					bFoundItem = true;

					int32 LocalNewQuantity = Items[i].ItemQuantity + LocalItemArray[j].ItemQuantity;

					LocalItemArray[j].ItemQuantity = LocalNewQuantity;
				}
			}

			if (bFoundItem)
				bFoundItem = false;

			else
			{
				FSimpleItemStruct FoundItems = FSimpleItemStruct();
				FoundItems.ItemID = Items[i].ItemID;
				FoundItems.ItemQuantity = Items[i].ItemQuantity;
				
				LocalItemArray.Emplace(FoundItems);
			}
		}
	}

	return LocalItemArray;
}

FItemsStruct UItemsContainerMaster::GetItemAtIndex(const int32 Index)
{
	if (Items.IsValidIndex(Index))
		return Items[Index];
	
	return FItemsStruct();
}

void UItemsContainerMaster::UpdateUI(const int32 Index, const FItemsStruct& ItemInfo) const
{
	switch (ContainerType)
	{
	case EContainerType::ECT_Inventory:

		if (const TObjectPtr<APlayerCharacter> PlayerRef = IPlayerCharacterInterface::Execute_GetPlayerRef(GetOwner()); IsValid(PlayerRef))
			IPlayerCharacterInterface::Execute_UpdateItem(PlayerRef, ContainerType, Index, ItemInfo);
		
		break;
		
	case EContainerType::ECT_HotBar:

		if (const TObjectPtr<APlayerCharacter> PlayerRef = IPlayerCharacterInterface::Execute_GetPlayerRef(GetOwner()); IsValid(PlayerRef))
			IPlayerCharacterInterface::Execute_UpdateItem(PlayerRef, ContainerType, Index, ItemInfo);
		
		break;
		
	case EContainerType::ECT_Storage:
		break;
		
	case EContainerType::ECT_Armour:
		break;

	default:
		break;
	}
}

bool UItemsContainerMaster::HasItemsToStack(const FItemsStruct& ItemInfo)
{
	for (const auto& Item : Items)
	{
		if (Item.ItemID == ItemInfo.ItemID && Item.ItemQuantity < Item.StackSize)
			return true;
	}
	
	return false;
}

int32 UItemsContainerMaster::SetTotalItemQuantity(const FItemsStruct& Item, const int32 Index)
{
	int32 Val = Item.ItemQuantity - (Items[Index].StackSize - Items[Index].ItemQuantity);

	int32 A = UKismetMathLibrary::Clamp(Val, 0, Item.ItemQuantity);

	if (Items[Index].ItemQuantity + Item.ItemQuantity >= Items[Index].StackSize)
		return A;
	
	return 0;
}

int32 UItemsContainerMaster::SetTotalItemQuantity(const int32 Slot, const int32 Total, const int32 Max)
{
	int32 Val = Total - (Max - Slot);

	int32 A = UKismetMathLibrary::Clamp(Val, 0, Total);

	if (Slot + Total >= Max)
		return A;

	return 0;
}

int32 UItemsContainerMaster::SetTotalItem(const int32 InTotalItemQuantity, const int32 InTempSlotQuantity, const int32 InMaxStackSize, const int32 InCurrentSlotQuantity)
{
	int32 Val = InTotalItemQuantity - (InMaxStackSize - InTempSlotQuantity);

	int32 A = UKismetMathLibrary::Clamp(Val, NULL, InMaxStackSize);

	if (InCurrentSlotQuantity + InTotalItemQuantity >= InMaxStackSize)
		return A;

	return NULL;
}

int32 UItemsContainerMaster::SetCurrentSlotQuantity(const int32 CurrentSlot, const int32 TotalQuantity, const int32 MaxQuantity)
{
	if (CurrentSlot + TotalQuantity >= MaxQuantity)
		return MaxQuantity;

	int32 Result = CurrentSlot + TotalQuantity;
	
	return Result;
}

int32 UItemsContainerMaster::SetSlotQuantity(const int32 InSlotQuantity, const int32 InTotalItem, const int32 InMax)
{
	if (InSlotQuantity + InTotalItem >= InMax)
		return InMax;

	return InSlotQuantity + InTotalItem;
}

int32 UItemsContainerMaster::CalcTotalItemQuantity(const int32 InTemp, const int32 InItemQuan, const int32 InMaxSize, const int32 InCurrent)
{
	int32 Val = InItemQuan - (InMaxSize - InTemp);

	int32 A = UKismetMathLibrary::Clamp(Val, NULL, InItemQuan);

	if (InCurrent + InItemQuan >= InMaxSize)
		return A;

	return NULL;
}

bool UItemsContainerMaster::AddItemsToIndex(const FItemsStruct& ItemInfo, const int32 LocalSpecificIndex, const int32 LocalItemIndex)
{
	//ItemInfo = LocalItem
	//LocalSpecificIndex = LocalIndex
	//LocalItemIndex = LocalFromIndex

	if (IsSlotEmpty(LocalSpecificIndex))
	{
		if (Items.IsValidIndex(LocalItemIndex))
		{
			Items[LocalSpecificIndex] = ItemInfo;

			return true;
		}
	}

	return false;
}

bool UItemsContainerMaster::IsSlotEmpty(const int32 SlotIndex)
{
	if (Items[SlotIndex].ItemID == 0)
		return true;
	
	return false;
}

bool UItemsContainerMaster::RemoveItemAtIndex(const int32 IndexToRemove)
{
	Items[IndexToRemove] = FItemsStruct();
	
	return true;
}


void UItemsContainerMaster::OnSlotDrop(const TObjectPtr<UItemsContainerMaster>& FromContainer, const int32 FromIndex, const int32 DroppedIndex)
{
	HandleSlotDrop(FromContainer, FromIndex, DroppedIndex);
}

//Overriden by child classes
void UItemsContainerMaster::HandleSlotDrop(const TObjectPtr<UItemsContainerMaster> FromContainer, const int32 FromIndex, const int32 DroppedIndex){}
