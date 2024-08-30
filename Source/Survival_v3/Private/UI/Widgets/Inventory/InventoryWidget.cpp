#include "UI/Widgets/Inventory/InventoryWidget.h"
#include "UI/Common/CommonButton/CommonButton.h"
#include "UI/Widgets/Crafting/Container/CraftingContainer.h"
#include "Components/WidgetSwitcher.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(InventoryTabButton) && IsValid(CraftingTabButton))
	{
		InventoryTabButton->bUseText = true;

		CraftingTabButton->bUseText = true;
		
		InventoryTabButton->SetButtonText(FText::FromString("Inventory"));

		CraftingTabButton->SetButtonText(FText::FromString("Crafting"));

		InventoryTabButton->OnClicked().AddUObject(this, &ThisClass::OnInventoryTabButtonClicked);

		CraftingTabButton->OnClicked().AddUObject(this, &ThisClass::OnCraftingTabButtonClicked);
	}
}

void UInventoryWidget::ResetCraftingWindow()
{
	if (IsValid(InventorySwitcher))
		InventorySwitcher->SetActiveWidgetIndex(0);
}

void UInventoryWidget::OnInventoryTabButtonClicked()
{
	if (IsValid(InventorySwitcher))
		InventorySwitcher->SetActiveWidgetIndex(0);
}

void UInventoryWidget::OnCraftingTabButtonClicked()
{
	if (IsValid(InventorySwitcher) && IsValid(CraftingContainer))
	{
		InventorySwitcher->SetActiveWidgetIndex(1);

		CraftingContainer->InitSlots();
	}
}
