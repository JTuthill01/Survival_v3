#include "UI/Widgets/InventoryLayout/GameInventoryLayout.h"
#include "UI/Common/CommonButton/CommonButton.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Components/TextBlock.h"

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

