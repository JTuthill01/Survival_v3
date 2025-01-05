#include "UI/Widgets/Crafting/Ingredient/CraftingIngredient.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

UCraftingIngredient::UCraftingIngredient(const FObjectInitializer& Object) : Super(Object), ResourceIcon(nullptr), ResourceText(FText()), ResourceQuantity(NULL)
{
}

void UCraftingIngredient::NativeConstruct()
{
	Super::NativeConstruct();

	SetResourceName();

	ResourceImage->SetBrushFromTexture(ResourceIcon);
}

void UCraftingIngredient::SetResourceName()
{
	FFormatNamedArguments Arguments;
	Arguments.Emplace("Quantity", FText::AsNumber(ResourceQuantity));
	Arguments.Emplace("Resource", ResourceText);

	ResourceName->SetText(FText::Format(NSLOCTEXT("RESOURCE", "R", "[x{Quantity} {Resource}]"), Arguments));
}
