#include "UI/Widgets/Main/MainUILayout.h"
#include "UI/Widgets/HUD/DefaultHUDLayout.h"
#include "UI/Widgets/InventoryLayout/GameInventoryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UMainUILayout::PushDefaultHUDLayout()
{
	if (IsValid(GameHUDStack))
		DefaultHUDLayout = GameHUDStack->AddWidget<UDefaultHUDLayout>(ActivatableWidgetSubclass);
}

void UMainUILayout::PushGameInventoryLayout()
{
	if (IsValid(GameInventoryStack))
		GameInventoryLayout = GameInventoryStack->AddWidget<UGameInventoryLayout>(GameInventoryWidgetSubclass);
}
