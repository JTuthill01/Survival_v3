#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class SURVIVAL_V3_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void ResetCraftingWindow();

	UFUNCTION()
	void OnInventoryTabButtonClicked();

	UFUNCTION()
	void OnCraftingTabButtonClicked();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UItemContainerGrid> WBP_ItemContainerGrid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCommonButton> InventoryTabButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButton> CraftingTabButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> InventorySwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCraftingContainer> CraftingContainer;
};
