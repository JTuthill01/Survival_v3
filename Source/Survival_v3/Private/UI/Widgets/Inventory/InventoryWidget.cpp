#include "UI/Widgets/Inventory/InventoryWidget.h"
#include "UI/Common/CommonButton/CommonButton.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(CommonButton01) && IsValid(CommonButton02))
	{
		CommonButton01->bUseText = true;

		CommonButton02->bUseText = true;
		
		CommonButton01->SetButtonText(FText::FromString("Inventory"));

		CommonButton02->SetButtonText(FText::FromString("Crafting"));
	}
}
