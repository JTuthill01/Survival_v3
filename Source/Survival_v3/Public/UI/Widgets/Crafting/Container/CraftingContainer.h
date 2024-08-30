#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "Structs/Crafting/ItemRecipeStruct.h"
#include "Structs/ItemsStructs/ItemStruct.h"
#include "Structs/Recipes/ItemRecipes.h"
#include "CraftingContainer.generated.h"

UCLASS()
class SURVIVAL_V3_API UCraftingContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	UCraftingContainer(const FObjectInitializer& Object);

	void InitSlots();

	void UpdateSlots(ECraftingType InType, const TArray<FSimpleItemStruct>& InItemArray);

	void AddSlots(ECraftingType CType, const TArray<FSimpleItemStruct>& ItemArray, bool AdminMode = false);

	void AddSlotsToGrid(int32 Index, class UCraftingSlot* CSlot);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	EContainerType ContainerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	ECraftingType CraftingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TArray<UCraftingSlot*> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 SlotsPerRow;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crafting")
	TObjectPtr<UCraftingSlot> CraftSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Subclass")
	TSubclassOf<UCraftingSlot> CraftingSlotSubclass;

private:
	FName GetPathName(ECraftingType CurrentType);

	TArray<FItemRecipeInfo> CheckIfCraftable(TArray<FItemRecipeStruct> RequiredItems, TArray<FSimpleItemStruct> ItemArray, bool& CanCraft);
};
