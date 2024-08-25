#include "UI/Common/CommonButton/CommonButton.h"

#include "Components/TextBlock.h"

UCommonButton::UCommonButton(const FObjectInitializer& Object) : Super(Object), DisplayText(FText()), bUseText(false)
{
}

void UCommonButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (bUseText)
		ButtonText->SetText(DisplayText);
}
