#include "UI/Widgets/Hotbar/HotbarWidget.h"
#include "UI/Widgets/Grid/ItemContainerGrid.h"

UHotbarWidget::UHotbarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UHotbarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(ItemContainerGrid))
	{
		ItemContainerGrid->SetContainerType(EContainerType::ECT_HotBar);
		
		ItemContainerGrid->SetShouldScroll(false);
	}
}
