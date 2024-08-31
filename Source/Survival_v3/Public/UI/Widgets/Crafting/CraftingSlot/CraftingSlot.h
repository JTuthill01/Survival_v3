#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "Structs/Recipes/ItemRecipes.h"
#include "CraftingSlot.generated.h"

UCLASS()
class SURVIVAL_V3_API UCraftingSlot : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UCraftingSlot(const FObjectInitializer& Object);

	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
#pragma region Variables_Bindings
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> ItemIconImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> CraftingBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UTexture2D> ImageTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	bool bCanCraftItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	EContainerType ContainerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	ECraftingType CraftingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TArray<FItemRecipeInfo> RequiredItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TSoftObjectPtr<UObject> RecipeAsset;
#pragma endregion
};
