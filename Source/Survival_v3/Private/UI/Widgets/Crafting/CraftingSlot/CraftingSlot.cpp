#include "UI/Widgets/Crafting/CraftingSlot/CraftingSlot.h"

#include "Components/Border.h"
#include "Components/Image.h"

UCraftingSlot::UCraftingSlot(const FObjectInitializer& Object) : Super(Object), bCanCraftItem(false), ItemID(0), ItemIndex(0), ContainerType(EContainerType::ECT_Inventory),
	CraftingType(ECraftingType::ECT_PlayerInventory), ItemName(FText())
{
}

void UCraftingSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(ItemIconImage) && IsValid(CraftingBackground))
	{
		ItemIconImage->SetBrushFromTexture(ItemIcon);

		if (bCanCraftItem)
		{
			FSlateColor IconTint = FSlateColor(FColor::FromHex("#4D4D4F"));

			FLinearColor CraftingBackgroundColor = FLinearColor(1.0, 1.0, 1.0, 0.5);
			
			ItemIconImage->SetBrushTintColor(IconTint);

			CraftingBackground->SetBrushColor(CraftingBackgroundColor);
		}

		else
		{
			FSlateColor IconTint = FSlateColor(FColor::White);

			FLinearColor CraftingBackgroundColor = FLinearColor(0.77, 0.77, 0.79, 1.0);

			ItemIconImage->SetBrushTintColor(IconTint);

			CraftingBackground->SetBrushColor(CraftingBackgroundColor);
		}
	}
}

void UCraftingSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UCraftingSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}
