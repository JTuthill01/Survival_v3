#include "UI/Widgets/Crafting/Info/CraftingInfo.h"
#include "UI/Widgets/Crafting/Item/CraftItemWidget.h"
#include "DataAssets/Primairy/ItemInfo.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

UCraftingInfo::UCraftingInfo(const FObjectInitializer& Object) : Super(Object)
{
}

void UCraftingInfo::InitializeWidget()
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(ItemAsset.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &ThisClass::OnLoadFinished));
}

void UCraftingInfo::OnLoadFinished()
{
	if (auto&& LocalInfo = Cast<UItemInfo>(ItemAsset.Get()); IsValid(LocalInfo))
	{
		FFormatNamedArguments Args;
		Args.Emplace(L"ItemName", ItemName);
		Args.Emplace(L"ItemType", FText::FromString(UEnum::GetValueAsString(LocalInfo->ItemType)));
		Args.Emplace(L"Rarity", FText::FromString(UEnum::GetValueAsString(LocalInfo->ItemRarity)));
	
		ItemNameText->SetText(FText::Format(NSLOCTEXT("ITEM", "Item", "[{ItemName} / {ItemType} / {Rarity}]"), Args));

		ItemDescriptionText->SetText(LocalInfo->ItemDescription);

		ItemIcon->SetBrushFromTexture(ImageIcon);

		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

		for (int32 i = 0; i < RequiredItems.Num(); ++i)
		{
			TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(RequiredItems[i].ItemIcon.ToSoftObjectPath(),
				FStreamableDelegate::CreateUObject(this, &ThisClass::OnItemIconLoadFinished, RequiredItems[i]));
		}
	}
}

void UCraftingInfo::OnItemIconLoadFinished(FItemRecipeInfo Info)
{
	if(CraftItem = CreateWidget<UCraftItemWidget>(this, CraftItemClassRef); IsValid(CraftItem))
	{
		CraftItem->ItemImage = Info.ItemIcon.Get();
		CraftItem->ItemName = Info.ItemName;
		CraftItem->NeededQuantity = Info.NeededQuantity;
		CraftItem->CurrentQuantity =  Info.CurrentQuantity;

		RequiredItemsBox->AddChild(CraftItem);
	}
}
