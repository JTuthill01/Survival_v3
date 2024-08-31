#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Recipes/ItemRecipes.h"
#include "CraftingInfo.generated.h"

UCLASS()
class SURVIVAL_V3_API UCraftingInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	UCraftingInfo(const FObjectInitializer& Object);

	void InitializeWidget();

	UPROPERTY()
	TObjectPtr<class UCraftItemWidget> CraftItem;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> RequiredItemsBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDescriptionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TSoftObjectPtr<class UItemInfo> ItemAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UTexture2D> ImageIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TSubclassOf<UCraftItemWidget> CraftItemClassRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TArray<FItemRecipeInfo> RequiredItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	FText ItemName;

private:
	void OnLoadFinished();

	void OnItemIconLoadFinished(FItemRecipeInfo Info);
};
