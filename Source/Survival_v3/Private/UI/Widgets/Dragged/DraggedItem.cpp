#include "UI/Widgets/Dragged/DraggedItem.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UDraggedItem::UDraggedItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), TextTop(FText()), Quantity(FText()), Weight(FText()), CurrentAmmo(0), MaxAmmo(0), CurrentHP(0),
	MaxHP(0), ItemType(EItemType::EIT_Resource), bUsesAmmo(false)
{
}

void UDraggedItem::NativeConstruct()
{
	Super::NativeConstruct();

	WeightText->SetText(Weight);
	WeightText->SetVisibility(ESlateVisibility::Visible);

	ItemIcon->SetBrushFromTexture(ImageIcon);
	ItemIcon->SetVisibility(ESlateVisibility::Visible);

	switch (ItemType)
	{
	case EItemType::EIT_Resource:

		SetResourceText();
		
		break;
		
	case EItemType::EIT_Equippable:

		SetEquippableText();
		
		break;
		
	case EItemType::EIT_Armour:

		SetArmorText();
		
		break;
		
	case EItemType::EIT_Consumable:

		SetConsumableText();
		
		break;
		
	case EItemType::EIT_Buildable:

		SetResourceText();
		
		break;

	default:
			break;
	}
}

void UDraggedItem::SetResourceText()
{
	FFormatNamedArguments Arguments;
	Arguments.Emplace(L"Quantity", Quantity);

	QuantityText->SetText(FText::Format(NSLOCTEXT("QUANTITY", "Q","x{Quantity}"), Arguments));
	QuantityText->SetVisibility(ESlateVisibility::Visible);

	TopText->SetVisibility(ESlateVisibility::Hidden);

	BottomText->SetVisibility(ESlateVisibility::Hidden);

	ItemHP->SetVisibility(ESlateVisibility::Hidden);
}

void UDraggedItem::SetEquippableText()
{
	FFormatNamedArguments Arguments;
	Arguments.Emplace(L"Amount", TextTop);

	TopText->SetText(FText::Format(NSLOCTEXT("DAMAGE", "Damage","DMG{Amount}%"), Arguments));
	TopText->SetVisibility(ESlateVisibility::Visible);

	QuantityText->SetVisibility(ESlateVisibility::Hidden);

	const double CurrentPercent = CurrentHP / MaxHP;

	ItemHP->SetVisibility(ESlateVisibility::Visible);
	ItemHP->SetPercent(CurrentPercent);

	if (bUsesAmmo)
	{
		FFormatNamedArguments Arg;
		Arg.Emplace(L"Current", FText::AsNumber(CurrentAmmo));
		Arg.Emplace(L"Max", FText::AsNumber(MaxAmmo));
		
		BottomText->SetVisibility(ESlateVisibility::Visible);
		
		BottomText->SetText(FText::Format(NSLOCTEXT("AMMO", "Ammo", "[{Current}/{Max}]"), Arg));
	}

	else
		BottomText->SetVisibility(ESlateVisibility::Hidden);
}

void UDraggedItem::SetArmorText()
{
	FFormatNamedArguments Arguments;
	Arguments.Emplace(L"ArmorAmount", TextTop);
	
	TopText->SetText(FText::Format(NSLOCTEXT("ARMOR", "A", "Armor{ArmorAmount}"), Arguments));
	TopText->SetVisibility(ESlateVisibility::Visible);

	QuantityText->SetVisibility(ESlateVisibility::Hidden);

	BottomText->SetVisibility(ESlateVisibility::Hidden);

	const double CurrentPercent = CurrentHP / MaxHP;

	ItemHP->SetVisibility(ESlateVisibility::Visible);
	ItemHP->SetPercent(CurrentPercent);
}

void UDraggedItem::SetConsumableText()
{
	FFormatNamedArguments Arguments;
	Arguments.Emplace(L"Quantity", Quantity);
	
	QuantityText->SetText(FText::Format(NSLOCTEXT("QUANTITY", "Q", "x{Quantity}"), Arguments));
	QuantityText->SetVisibility(ESlateVisibility::Visible);

	BottomText->SetVisibility(ESlateVisibility::Hidden);

	TopText->SetVisibility(ESlateVisibility::Hidden);

	const double CurrentPercent = CurrentHP / MaxHP;

	ItemHP->SetVisibility(ESlateVisibility::Visible);
	ItemHP->SetPercent(CurrentPercent);
}
