#include "UI/Widgets/Slot/InventorySlot.h"

#include "Character/Player/PlayerCharacter.h"
#include "UI/Widgets/Dragged/DraggedItem.h"
#include "DataAssets/Primairy/ItemInfo.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/DragDrop/ItemDrag.h"

UInventorySlot::UInventorySlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), ItemIndex(0), ContainerType(EContainerType::ECT_Inventory), bHasItemInSlot(false),
	ItemInfos(FItemsStruct())
{
}

//Set Item Slot depending on item type
void UInventorySlot::UpdateSlot(const FItemsStruct& ItemInfo)
{
	bHasItemInSlot = true;

	ItemInfos = ItemInfo;

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	FSoftObjectPath Path = ItemInfo.ItemAsset.ToSoftObjectPath();

	TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(Path, FStreamableDelegate::CreateUObject(this, &ThisClass::OnLoadComplete));
}

void UInventorySlot::ResetInventorySlot()
{
	BottomText->SetVisibility(ESlateVisibility::Hidden);

	ItemHP->SetVisibility(ESlateVisibility::Hidden);

	ItemIcon->SetVisibility(ESlateVisibility::Hidden);

	QuantityText->SetVisibility(ESlateVisibility::Hidden);

	TopText->SetVisibility(ESlateVisibility::Hidden);

	WeightText->SetVisibility(ESlateVisibility::Hidden);

	bHasItemInSlot = false;

	ItemInfos = FItemsStruct();
}

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);

		return Reply;
	}
	
	return FReply::Unhandled();
}

FReply UInventorySlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply =  Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		
		return Reply;
	}
	
	return FReply::Unhandled();
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (bHasItemInSlot)
	{
		if (DraggedWidget = CreateWidget<UDraggedItem>(GetWorld(), DraggedItemSubclass); IsValid(DraggedWidget))
		{
			if (IsValid(ItemAssetInfo))
			{
				const double CurrentWeight = ItemInfos.ItemQuantity * ItemAssetInfo->ItemWeight;
				
				DraggedWidget->SetImageIcon(ItemAssetInfo->ItemIcon);
				DraggedWidget->SetTextTop(FText::AsNumber(ItemAssetInfo->ItemDamage));
				DraggedWidget->SetItemType(ItemAssetInfo->ItemType);
				DraggedWidget->SetQuantity(FText::AsNumber(ItemInfos.ItemQuantity));
				DraggedWidget->SetUsesAmmo(ItemAssetInfo->bDoesUseAmmo);
				DraggedWidget->SetCurrentAmmo(ItemInfos.CurrentAmmo);
				DraggedWidget->SetMaxAmmo(ItemInfos.MaxAmmo);
				DraggedWidget->SetWeight(FText::AsNumber(CurrentWeight));
				DraggedWidget->SetCurrentHP(ItemInfos.CurrentHP);
				DraggedWidget->SetMaxHP(ItemInfos.MaxHP);

				if (const TObjectPtr<UItemDrag> DragDropOperation = NewObject<UItemDrag>(); IsValid(DragDropOperation))
				{
					DragDropOperation->DefaultDragVisual = DraggedWidget;
					
					DragDropOperation->SetItemDragVariables(ItemIndex, ContainerType, ItemAssetInfo->ItemType, ItemAssetInfo->ArmourType);

					OutOperation = DragDropOperation;
				}
			}
		}
	}
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (const TObjectPtr<UItemDrag> LocalItemDrag = Cast<UItemDrag>(InOperation); IsValid(LocalItemDrag))
	{
		int32 LocalSlotIndex;

		EContainerType LocalFromContainer;

		EArmourType LocalArmorType;

		EItemType LocalItemType;
		
		IItemDragInterface::Execute_GetItemDragInfo(LocalItemDrag, LocalSlotIndex, LocalFromContainer, LocalArmorType, LocalItemType);

		if (const TObjectPtr<APlayerCharacter> PlayerRef = IPlayerCharacterInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)); IsValid(PlayerRef))
		{
			IPlayerCharacterInterface::Execute_OnSlotDropped(PlayerRef, ContainerType, LocalFromContainer, LocalSlotIndex, ItemIndex, LocalArmorType);

			return true;
		}
	}
	
	return false;
}

void UInventorySlot::SetResourceText(const FItemsStruct& ItemInfo) const
{
	FFormatNamedArguments Arguments;
	Arguments.Emplace(L"Quantity", FText::AsNumber(ItemInfo.ItemQuantity));

	QuantityText->SetText(FText::Format(NSLOCTEXT("QUANTITY", "Q","x{Quantity}"), Arguments));
	QuantityText->SetVisibility(ESlateVisibility::Visible);

	TopText->SetVisibility(ESlateVisibility::Hidden);

	BottomText->SetVisibility(ESlateVisibility::Hidden);

	ItemHP->SetVisibility(ESlateVisibility::Hidden);
}

void UInventorySlot::SetEquippableQuantityText(const FItemsStruct& ItemInfo) const
{
	FFormatNamedArguments Arguments;
	Arguments.Emplace(L"Amount", FText::AsNumber(ItemAssetInfo->ItemDamage));

	TopText->SetText(FText::Format(NSLOCTEXT("DAMAGE", "Damage","DMG{Amount}%"), Arguments));
	TopText->SetVisibility(ESlateVisibility::Visible);

	QuantityText->SetVisibility(ESlateVisibility::Hidden);

	const double CurrentPercent = ItemInfo.CurrentHP / ItemInfo.MaxHP;

	ItemHP->SetVisibility(ESlateVisibility::Visible);
	ItemHP->SetPercent(CurrentPercent);

	if (ItemAssetInfo->bDoesUseAmmo)
	{
		FFormatNamedArguments Arg;
		Arg.Emplace(L"Current", FText::AsNumber(ItemInfo.CurrentAmmo));
		Arg.Emplace(L"Max", FText::AsNumber(ItemInfo.MaxAmmo));
		
		BottomText->SetVisibility(ESlateVisibility::Visible);
		
		BottomText->SetText(FText::Format(NSLOCTEXT("AMMO", "Ammo", "[{Current}/{Max}]"), Arg));
	}

	else
		BottomText->SetVisibility(ESlateVisibility::Hidden);
}

void UInventorySlot::SetArmorText(const FItemsStruct& ItemInfo) const
{
	FFormatNamedArguments Arguments;
	Arguments.Emplace(L"ArmorAmount", FText::AsNumber(ItemAssetInfo->ItemDamage));
	
	TopText->SetText(FText::Format(NSLOCTEXT("ARMOR", "A", "Armor{ArmorAmount}"), Arguments));
	TopText->SetVisibility(ESlateVisibility::Visible);

	QuantityText->SetVisibility(ESlateVisibility::Hidden);

	BottomText->SetVisibility(ESlateVisibility::Hidden);

	const double CurrentPercent = ItemInfo.CurrentHP / ItemInfo.MaxHP;

	ItemHP->SetVisibility(ESlateVisibility::Visible);
	ItemHP->SetPercent(CurrentPercent);
}

void UInventorySlot::SetConsumableText(const FItemsStruct& ItemInfo) const
{
	FFormatNamedArguments Arguments;
	Arguments.Emplace(L"Quantity", FText::AsNumber(ItemInfo.ItemQuantity));
	
	QuantityText->SetText(FText::Format(NSLOCTEXT("QUANTITY", "Q", "x{Quantity}"), Arguments));
	QuantityText->SetVisibility(ESlateVisibility::Visible);

	BottomText->SetVisibility(ESlateVisibility::Hidden);

	TopText->SetVisibility(ESlateVisibility::Hidden);

	const double CurrentPercent = ItemInfo.CurrentHP / ItemInfo.MaxHP;

	ItemHP->SetVisibility(ESlateVisibility::Visible);
	ItemHP->SetPercent(CurrentPercent);
}

void UInventorySlot::OnLoadComplete()
{
	ItemAssetInfo = ItemInfos.ItemAsset.Get();

	if (IsValid(ItemAssetInfo))
	{
		const double TotalWeight = ItemAssetInfo->ItemWeight * ItemInfos.ItemQuantity;

		FNumberFormattingOptions Options;
		Options.MaximumFractionalDigits = 0;
		Options.MinimumIntegralDigits = 3;
		Options.MaximumIntegralDigits = 3;
		
		WeightText->SetText(FText::AsNumber(TotalWeight, &Options));

		WeightText->SetVisibility(ESlateVisibility::Visible);

		ItemIcon->SetBrushFromTexture(ItemAssetInfo->ItemIcon);

		ItemIcon->SetVisibility(ESlateVisibility::Visible);

		switch (ItemAssetInfo->ItemType)
		{
		case EItemType::EIT_Resource:

			SetResourceText(ItemInfos);
				
			break;
				
		case EItemType::EIT_Equippable:

			SetEquippableQuantityText(ItemInfos);
				
			break;
				
		case EItemType::EIT_Armour:

			SetArmorText(ItemInfos);
				
			break;
				
		case EItemType::EIT_Consumable:

			SetConsumableText(ItemInfos);
				
			break;
				
		case EItemType::EIT_Buildable:

			SetResourceText(ItemInfos);
				
			break;

		default:
			break;
		}
	}
}

