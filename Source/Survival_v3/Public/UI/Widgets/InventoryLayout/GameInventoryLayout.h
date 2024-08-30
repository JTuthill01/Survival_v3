#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Structs/ItemsStructs/ItemStruct.h"
#include "Structs/Recipes/ItemRecipes.h"
#include "GameInventoryLayout.generated.h"

class UWidgetSwitcher;

UCLASS()
class SURVIVAL_V3_API UGameInventoryLayout : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCloseClicked();

	UFUNCTION()
	void OnWidgetDeactivated();

	void UpdateCraftWidget(ECraftingType InType, const TArray<FSimpleItemStruct>& ItemStruct);

	UPROPERTY()
	TObjectPtr<class APlayerCharacterController> PC;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> InventoryWidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UInventoryWidget> WBP_Inventory;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCommonButton> WBP_CommonButton;
};
