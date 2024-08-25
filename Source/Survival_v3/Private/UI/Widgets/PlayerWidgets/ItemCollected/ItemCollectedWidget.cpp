#include "UI/Widgets/PlayerWidgets/ItemCollected/ItemCollectedWidget.h"
#include "Animation/WidgetAnimationEvents.h"
#include "Components/TextBlock.h"

UItemCollectedWidget::UItemCollectedWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), ResourceQuantity(0), ResourceName(FText())
{
}

void UItemCollectedWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(FadeOut);

	FWidgetAnimationDynamicEvent Delegate;
	Delegate.BindDynamic(this, &UItemCollectedWidget::DestroySelf);

	BindToAnimationFinished(FadeOut, Delegate);

	OnResourceTextBlockChange.AddDynamic(this, &ThisClass::SetResourceText);
}

void UItemCollectedWidget::SetVariables(const TObjectPtr<UTexture2D>& InIcon, const int32 InResourceQuantity, const FText& InResourceName)
{
	ResourceImage = InIcon;

	ResourceQuantity = InResourceQuantity;

	ResourceName = InResourceName;
}

void UItemCollectedWidget::SetResourceText(int32 NewQuantity, FText NewResource)
{
	FFormatNamedArguments Arguments;
	Arguments.Emplace(L"Quantity", FText::AsNumber(NewQuantity));
	Arguments.Emplace(L"Name", NewResource);
	
	ResourceName = FText::Format(NSLOCTEXT("RESOURCE", "Resource", "[x{Quantity} {Name}]"), Arguments);

	ResourceTextBlock->SetText(ResourceName);
}

void UItemCollectedWidget::DestroySelf() { RemoveFromParent(); }
