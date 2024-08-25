#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "ItemContainerGrid.generated.h"

UCLASS()
class SURVIVAL_V3_API UItemContainerGrid : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region Setters
	FORCEINLINE void SetSlotsPerRow(const int32 Value) { SlotsPerRow = Value; }
	FORCEINLINE void SetTotalSlots(const int32 Val) { TotalSlots = Val; }
	FORCEINLINE void SetContainerType(const EContainerType NewType) { ContainerType = NewType; }
	FORCEINLINE void SetShouldScroll(const bool NewVal) { bShouldScroll = NewVal; }
#pragma endregion

	FORCEINLINE TArray<TObjectPtr<class UInventorySlot>> GetSlots() const { return Slots;}
	
	UItemContainerGrid(const FObjectInitializer& ObjectInitializer);

#pragma region Bindings
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> Grid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> GridScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	int32 SlotsPerRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	int32 TotalSlots;
#pragma endregion

#pragma region Functions
	virtual void NativeConstruct() override;
	
	void AddSlots(int32 Amount);
	void AddSlotsToGrid(int32 Index, UInventorySlot* InSlot);
#pragma endregion

private:
#pragma region Pointer Variables
	UPROPERTY()
	TObjectPtr<UInventorySlot> InventorySlot;

	UPROPERTY()
	TArray<TObjectPtr<UInventorySlot>> Slots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GridVariables, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventorySlot> SlotSubclass;
#pragma endregion
	
#pragma region Variables
	EContainerType ContainerType;

	bool bShouldScroll;
#pragma endregion
};
