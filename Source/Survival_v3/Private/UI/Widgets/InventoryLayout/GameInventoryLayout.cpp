#include "UI/Widgets/InventoryLayout/GameInventoryLayout.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "UI/Common/CommonButton/CommonButton.h"
#include "UI/Widgets/Inventory/InventoryWidget.h"
#include "UI/Widgets/Crafting/Container/CraftingContainer.h"
#include "UI/Widgets/Crafting/Info/CraftingInfo.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Components/TextBlock.h"
#include "DataAssets/Recipes/ItemRecipe.h"
#include "Engine/AssetManager.h"

void UGameInventoryLayout::NativeConstruct()
{
	Super::NativeConstruct();

	PC = Cast<APlayerCharacterController>(GetOwningPlayer());

	if (IsValid(WBP_CommonButton))
	{
		WBP_CommonButton->SetUseText(true);

		WBP_CommonButton->ButtonText->SetText(FText::FromString("EXIT"));

		WBP_CommonButton->OnClicked().AddUObject(this, &ThisClass::OnCloseClicked);
	}

	OnDeactivated().AddUObject(this, &ThisClass::OnWidgetDeactivated);
}

void UGameInventoryLayout::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (IsValid(WBP_Inventory))
		WBP_Inventory->ResetCraftingWindow();
}

void UGameInventoryLayout::OnCloseClicked()
{
	DeactivateWidget();
}

void UGameInventoryLayout::OnWidgetDeactivated()
{
	if (IsValid(PC))
		IPlayerControllerInterface::Execute_CloseInventory(PC);
}

void UGameInventoryLayout::GameInventoryHideCraftItemToolTip() const
{
	if (IsValid(CraftToolTipRef))
		CraftToolTipRef->RemoveFromParent();
}

void UGameInventoryLayout::ShowCraftTooltip(UTexture2D* ItemIcon, TArray<FItemRecipeInfo> RequiredItems, const FText& ItemName, TSoftObjectPtr<UItemRecipe> RecipeAsset)
{
	if (IsValid(CraftToolTipRef))
		CraftToolTipRef->RemoveFromParent();

	else if (!IsValid(CraftToolTipRef))
	{
		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

		TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(RecipeAsset.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &ThisClass::OnAssetLoadedComplete,
			RequiredItems, RecipeAsset));
	}
}

void UGameInventoryLayout::OnAssetLoadedComplete(TArray<FItemRecipeInfo> RequiredItems, TSoftObjectPtr<UItemRecipe> RecipeAsset)
{
	if (CraftToolTipRef = CreateWidget<UCraftingInfo>(this, CraftingInfoClassRef); IsValid(CraftToolTipRef))
	{
		CraftToolTipRef->ImageIcon = RecipeAsset.Get()->ItemIcon;

		CraftToolTipRef->ItemName = RecipeAsset.Get()->ItemName;

		CraftToolTipRef->RequiredItems = RequiredItems;

		auto&& LocalAsset = RecipeAsset.Get();

		CraftToolTipRef->ItemAsset = LocalAsset->ItemAsset;

		CraftToolTipRef->InitializeWidget();

		CraftToolTipRef->AddToViewport(1);

		auto&& MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);

		double MousePosX = MousePosition.X + 10.0;
		double MousePosY = MousePosition.Y + 10.0;

		FVector2d NewMousePosition{MousePosX, MousePosY};

		CraftToolTipRef->SetPositionInViewport(NewMousePosition);
	}
}

void UGameInventoryLayout::UpdateCraftWidget(ECraftingType InType, const TArray<FSimpleItemStruct>& ItemStruct) const
{
	switch (InType)
	{
	case ECraftingType::ECT_PlayerInventory:

		WBP_Inventory->CraftingContainer->UpdateSlots(InType, ItemStruct);
		
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
}

