#include "UI/Widgets/Grid/ItemContainerGrid.h"
#include "UI/Widgets/Slot/InventorySlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/ScrollBox.h"
#include "Kismet/KismetMathLibrary.h"

UItemContainerGrid::UItemContainerGrid(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), SlotsPerRow(0), TotalSlots(0), ContainerType(EContainerType::ECT_Inventory),
	bShouldScroll(false)
{
}

void UItemContainerGrid::NativeConstruct()
{
	Super::NativeConstruct();

	AddSlots(TotalSlots);

	GridScrollBox->SetAlwaysShowScrollbar(bShouldScroll);
}

void UItemContainerGrid::AddSlots(const int32 Amount)
{
	//Amount = Local Loop Index

	for (int32 i = 0; i < Amount; ++i)
	{
		if (InventorySlot = CreateWidget<UInventorySlot>(GetOwningPlayer(), SlotSubclass); IsValid(InventorySlot))
		{
			InventorySlot->ContainerType = ContainerType;

			InventorySlot->ItemIndex = Slots.Emplace(InventorySlot);

			AddSlotsToGrid(InventorySlot->ItemIndex, InventorySlot);
		}
	}
}

void UItemContainerGrid::AddSlotsToGrid(int32 Index, UInventorySlot* InSlot)
{
	//Index = Local Slot Index
	//Slot = Local Slot

	if (IsValid(InSlot))
	{
		if (TObjectPtr<UUniformGridSlot> UniformGrid = Grid->AddChildToUniformGrid(InSlot); IsValid(UniformGrid))
		{
			double RemainderDouble;

			double IndexDouble = Index;
			double SlotsPerRowDouble = SlotsPerRow;

			double DivisionDouble = IndexDouble / SlotsPerRowDouble;

			UKismetMathLibrary::FMod(IndexDouble, SlotsPerRowDouble, RemainderDouble);

			int32 Row = UKismetMathLibrary::FTrunc(DivisionDouble);
			int32 Column = UKismetMathLibrary::FTrunc(RemainderDouble);

			UniformGrid->SetRow(Row);
			UniformGrid->SetColumn(Column);
		}
	}
}

