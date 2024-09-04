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

	virtual void NativeOnActivated() override;

	UFUNCTION()
	void OnCloseClicked();

	UFUNCTION()
	void OnWidgetDeactivated();

	void GameInventoryHideCraftItemToolTip() const;

	void UpdateCraftWidget(ECraftingType InType, const TArray<FSimpleItemStruct>& ItemStruct) const;

	void ShowCraftTooltip(UTexture2D* ItemIcon, TArray<FItemRecipeInfo> RequiredItems, const FText& ItemName, TSoftObjectPtr<class UItemRecipe> RecipeAsset);

	UPROPERTY()
	TObjectPtr<class APlayerCharacterController> PC;

	UPROPERTY()
	TObjectPtr<class UCraftingInfo> CraftToolTipRef;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> InventoryWidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UInventoryWidget> WBP_Inventory;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCommonButton> WBP_CommonButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UCraftingInfo> CraftingInfoClassRef;

	void OnAssetLoadedComplete(TArray<FItemRecipeInfo> RequiredItems, TSoftObjectPtr<UItemRecipe> RecipeAsset);
};
