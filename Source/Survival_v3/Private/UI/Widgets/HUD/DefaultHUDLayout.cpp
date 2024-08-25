#include "UI/Widgets/HUD/DefaultHUDLayout.h"
#include "Components/VerticalBox.h"
#include "UI/Widgets/PlayerWidgets/ItemCollected/ItemCollectedWidget.h"

void UDefaultHUDLayout::AddResources(UTexture2D* Icon, const int32 Quantity, const FText& Name)
{
	if (ItemCollectedWidget = CreateWidget<UItemCollectedWidget>(GetWorld(), ItemCollectedClassRef); IsValid(ItemCollectedWidget))
	{
		ItemCollectedWidget->SetVariables(Icon, Quantity, Name);

		ResourcesCollected->AddChild(ItemCollectedWidget);
	}
}
