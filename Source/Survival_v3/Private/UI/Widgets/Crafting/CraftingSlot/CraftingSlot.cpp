#include "UI/Widgets/Crafting/CraftingSlot/CraftingSlot.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

UCraftingSlot::UCraftingSlot(const FObjectInitializer& Object) : Super(Object), bCanCraftItem(false), ItemID(0), ItemIndex(0), ContainerType(EContainerType::ECT_Inventory),
	CraftingType(ECraftingType::ECT_PlayerInventory), ItemName(FText()), bShowTooltip(true)
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
			ItemIconImage->SetBrushTintColor(FSlateColor(FColor::FromHex("#4D4D4F")));

			CraftingBackground->SetBrushColor(FLinearColor(1.0, 1.0, 1.0, 0.5));
		}

		else
		{
			ItemIconImage->SetBrushTintColor(FSlateColor(FColor::White));

			CraftingBackground->SetBrushColor(FLinearColor(0.77, 0.77, 0.79, 1.0));
		}
	}
}

void UCraftingSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (bShowTooltip)
	{
		bShowTooltip = false;
		
		if (const TObjectPtr<APlayerCharacterController> PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); IsValid(PC))
			PC->ShowCraftItemTooltip(ImageTexture, ItemName, RequiredItems, RecipeAsset);
	}
}

void UCraftingSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	bShowTooltip = true;

	if (const TObjectPtr<APlayerCharacterController> PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); IsValid(PC))
		IPlayerControllerInterface::Execute_HideCraftItemToolTip(PC);
}

