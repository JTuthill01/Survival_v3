#include "UI/Widgets/Crafting/Item/CraftItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

UCraftItemWidget::UCraftItemWidget(const FObjectInitializer& Object) : Super(Object), ItemName(FText()), CurrentQuantity(0), NeededQuantity(0)
{
}

void UCraftItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();	

	TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(ItemImage.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &ThisClass::OnLoadFinished));
}

void UCraftItemWidget::OnLoadFinished()
{

	ItemIcon->SetBrushFromTexture(ItemImage.Get());
	
	FFormatNamedArguments Args;
	Args.Emplace("ItemName", ItemName);
	Args.Emplace("CurrentQuantity", FText::AsNumber(CurrentQuantity));
	Args.Emplace("NeededQuantity", FText::AsNumber(NeededQuantity));

	ItemText->SetText(FText::Format(NSLOCTEXT("CRAFT_ITEM", "Craft_Item", "[{ItemName} : {CurrentQuantity} / {NeededQuantity}]"), Args));
	
	if (CurrentQuantity >= NeededQuantity)
		ItemText->SetColorAndOpacity(FColor::FromHex("#004225"));

	else
		ItemText->SetColorAndOpacity(FColor::FromHex("#E42217"));
}
