#include "UI/Widgets/Crafting/Info/CraftingInfo.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataAssets/Primairy/ItemInfo.h"
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

		ItemIcon->SetBrushFromTexture(LocalInfo->ItemIcon);
	}
}
