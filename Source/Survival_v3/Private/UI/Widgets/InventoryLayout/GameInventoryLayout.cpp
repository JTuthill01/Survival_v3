#include "UI/Widgets/InventoryLayout/GameInventoryLayout.h"
#include "UI/Common/CommonButton/CommonButton.h"
#include "UI/Widgets/Inventory/InventoryWidget.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Components/TextBlock.h"
#include "UI/Widgets/Crafting/Container/CraftingContainer.h"

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

void UGameInventoryLayout::OnCloseClicked()
{
	DeactivateWidget();
}

void UGameInventoryLayout::OnWidgetDeactivated()
{
	if (IsValid(PC))
		IPlayerControllerInterface::Execute_CloseInventory(PC);
}

void UGameInventoryLayout::UpdateCraftWidget(ECraftingType InType, const TArray<FSimpleItemStruct>& ItemStruct)
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

