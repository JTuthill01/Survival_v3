#include "UI/Widgets/Crafting/Container/CraftingContainer.h"
#include "DataAssets/Recipes/ItemRecipe.h"
#include "DataAssets/Primairy/ItemInfo.h"
#include "UI/Widgets/Crafting/CraftingSlot/CraftingSlot.h"
#include "Character/Player/PlayerCharacter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Kismet/KismetMathLibrary.h"

UCraftingContainer::UCraftingContainer(const FObjectInitializer& Object) : Super(Object), ContainerType(EContainerType::ECT_Inventory), CraftingType(ECraftingType::ECT_PlayerInventory), SlotsPerRow(6)
{
}

void UCraftingContainer::InitSlots()
{
	if (const TObjectPtr<APlayerCharacter> PlayerRef = IPlayerCharacterInterface::Execute_GetPlayerRef(GetOwningPlayerPawn()); IsValid(PlayerRef))
		IPlayerCharacterInterface::Execute_GetEndGramsAndItems(PlayerRef, CraftingType);
}

void UCraftingContainer::UpdateSlots(ECraftingType InType, const TArray<FSimpleItemStruct>& InItemArray)
{
	CraftingType = InType;

	Grid->ClearChildren();

	Slots.Empty();

	AddSlots(InType, InItemArray);
}

void UCraftingContainer::AddSlots(ECraftingType CType, const TArray<FSimpleItemStruct>& ItemArray, bool AdminMode)
{
	//LocalItemArray = ItemArray

	switch (CType)
	{
	case ECraftingType::ECT_PlayerInventory:

		if (AdminMode == false)
		{
			FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

			if (TArray<FAssetData> AssetData; AssetRegistryModule.Get().GetAssetsByPath(GetPathName(CType), AssetData, true))
			{
				for (int i = 0; i < AssetData.Num(); ++i)
				{
					if (auto&& LocalItemRecipe = Cast<UItemRecipe>(AssetData[i].GetAsset()); IsValid(LocalItemRecipe))
					{
						bool bCraft = false;
						
						auto&& ReturnedItems = CheckIfCraftable(LocalItemRecipe->RequiredItems, ItemArray, bCraft);

						if (CraftSlot = CreateWidget<UCraftingSlot>(GetWorld(), CraftingSlotSubclass); IsValid(CraftSlot))
						{
							CraftSlot->bCanCraftItem = bCraft;
							CraftSlot->ItemIcon = LocalItemRecipe->ItemIcon;
							CraftSlot->ItemID = LocalItemRecipe->ItemID;
							CraftSlot->ItemName = LocalItemRecipe->ItemName;
							CraftSlot->ContainerType = ContainerType;
							CraftSlot->RequiredItems = ReturnedItems;
							CraftSlot->CraftingType = CraftingType;
							CraftSlot->RecipeAsset = LocalItemRecipe->ItemAsset;

							CraftSlot->ItemIndex = Slots.Emplace(CraftSlot);

							AddSlotsToGrid(CraftSlot->ItemIndex, CraftSlot);
						}
					}
				}
			}
		}
		
		break;
		
	case ECraftingType::ECT_CookingPot:
		break;
		
	case ECraftingType::ECT_CraftingBench:

		if (AdminMode == false)
		{
			FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

			TArray<FAssetData> AssetData;

			AssetRegistryModule.Get().GetAssetsByPath(GetPathName(CType), AssetData, true);
		}
		
		break;
		
	case ECraftingType::ECT_SmeltingForge:
		break;
		
	case ECraftingType::ECT_AdvancedWorkbench:

		if (AdminMode == false)
		{
			FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

			TArray<FAssetData> AssetData;

			AssetRegistryModule.Get().GetAssetsByPath(GetPathName(CType), AssetData, true);
		}
		
		break;
		
	case ECraftingType::ECT_StorageBox:
		break;
		
	case ECraftingType::ECT_CropPlot:
		break;

	default:
		break;
	}
}

void UCraftingContainer::AddSlotsToGrid(int32 Index, class UCraftingSlot* CSlot)
{
	int32 LocalSlotIndex = Index;

	if (IsValid(Grid))
	{
		if (auto&& Panel = Grid->AddChildToUniformGrid(CSlot); IsValid(Panel))
		{
			const double InRowDouble = LocalSlotIndex / SlotsPerRow;

			const int32 InRowInt = UKismetMathLibrary::FTrunc(InRowDouble);
			
			Panel->SetRow(InRowInt);

			double Remainder;

			UKismetMathLibrary::FMod(LocalSlotIndex, SlotsPerRow, Remainder);
			
			Panel->SetColumn(UKismetMathLibrary::FTrunc(Remainder));
		}
	}
}

FName UCraftingContainer::GetPathName(const ECraftingType CurrentType)
{
	FName OutName = NAME_None;

	switch (CurrentType)
	{
	case ECraftingType::ECT_PlayerInventory:

		OutName = "/Game/_Main/Blueprints/DataAssets/CraftingAssets/PlayerInventory";
		
		break;
		
	case ECraftingType::ECT_CookingPot:
		break;
		
	case ECraftingType::ECT_CraftingBench:
		break;
		
	case ECraftingType::ECT_SmeltingForge:
		break;
		
	case ECraftingType::ECT_AdvancedWorkbench:
		break;
		
	case ECraftingType::ECT_StorageBox:
		break;
		
	case ECraftingType::ECT_CropPlot:
		break;

	default:
		break;
	}

	return OutName;
}

TArray<FItemRecipeInfo> UCraftingContainer::CheckIfCraftable(TArray<FItemRecipeStruct> RequiredItems, TArray<FSimpleItemStruct> ItemArray, bool& CanCraft)
{
	//LocalRequiredItems = RequiredItems
	//LocalItemArray = ItemArray

	TArray<FItemRecipeInfo> LocalItemsInInventory;

	bool bDoesNotContainItem = false;
	bool bIsFound = false;
	
	for (int32 i = 0; i < RequiredItems.Num(); ++i)
	{
		if (ItemArray.Num() == 0)
		{
			FItemRecipeInfo TempRecipe;

			TempRecipe.NeededQuantity = RequiredItems[i].ItemQuantity;
			TempRecipe.ItemID = RequiredItems[i].ItemID;
			TempRecipe.ItemIcon = RequiredItems[i].ItemIcon;

			LocalItemsInInventory.Emplace(TempRecipe);

			bDoesNotContainItem = false;
		}

		else
		{
			for (int32 j = 0; j < ItemArray.Num(); ++j)
			{
				if (ItemArray[j].ItemID == RequiredItems[i].ItemID)
				{
					bIsFound = true;

					if (ItemArray[j].ItemQuantity > RequiredItems[i].ItemQuantity)
					{
						FItemRecipeInfo TempRecipe;

						TempRecipe.ItemID = RequiredItems[i].ItemID;
						TempRecipe.ItemIcon = RequiredItems[i].ItemIcon;
						TempRecipe.ItemName = RequiredItems[i].ItemName;
						TempRecipe.CurrentQuantity = ItemArray[j].ItemQuantity;
						TempRecipe.NeededQuantity = RequiredItems[i].ItemQuantity;

						LocalItemsInInventory.Emplace(TempRecipe);
					}

					else
					{
						bDoesNotContainItem = true;

						FItemRecipeInfo TempRecipe;

						TempRecipe.ItemID = RequiredItems[i].ItemID;
						TempRecipe.ItemIcon = RequiredItems[i].ItemIcon;
						TempRecipe.ItemName = RequiredItems[i].ItemName;
						TempRecipe.CurrentQuantity = ItemArray[j].ItemQuantity;
						TempRecipe.NeededQuantity = RequiredItems[i].ItemQuantity;

						LocalItemsInInventory.Emplace(TempRecipe);
					}
				}
			}

			if (bIsFound)
				bIsFound = false;

			else
			{
				FItemRecipeInfo TempRecipe;

				TempRecipe.ItemID = RequiredItems[i].ItemID;
				TempRecipe.CurrentQuantity = NULL;
				TempRecipe.ItemIcon = RequiredItems[i].ItemIcon;
				TempRecipe.ItemName = RequiredItems[i].ItemName;
				TempRecipe.NeededQuantity = RequiredItems[i].ItemQuantity;

				LocalItemsInInventory.Emplace(TempRecipe);

				bDoesNotContainItem = true;
			}
		}
	}

	CanCraft = !bDoesNotContainItem;
	
	return LocalItemsInInventory;
}
