#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "Structs/ItemsStructs/ItemStruct.h"
#include "InventorySlot.generated.h"

UCLASS()
class SURVIVAL_V3_API UInventorySlot : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UInventorySlot(const FObjectInitializer& ObjectInitializer);

	void UpdateSlot(const FItemsStruct& ItemInfo);

	void ResetInventorySlot();

#pragma region Virtual Functions
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnPreviewMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	virtual void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation ) override;

	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
#pragma endregion //Virtual Functions

#pragma region Variables
	int32 ItemIndex;

	EContainerType ContainerType;

	bool bHasItemInSlot;
#pragma endregion
	
#pragma region Bindings
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> SlotStyle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TopText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BottomText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WeightText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ItemHP;
#pragma endregion

private:
#pragma region Private Functions
	void SetResourceText(const FItemsStruct& ItemInfo) const;

	void SetEquippableQuantityText(const FItemsStruct& ItemInfo) const;

	void SetArmorText(const FItemsStruct& ItemInfo) const;

	void SetConsumableText(const FItemsStruct& ItemInfo) const;

	void OnLoadComplete();
#pragma endregion

	UPROPERTY()
	TObjectPtr<UItemInfo> ItemAssetInfo;

	UPROPERTY()
	TObjectPtr<class UDraggedItem> DraggedWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Subclass", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDraggedItem> DraggedItemSubclass;

	FItemsStruct ItemInfos;
};
