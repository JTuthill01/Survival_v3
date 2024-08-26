#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "CraftingSlot.generated.h"

USTRUCT(BlueprintType)
struct FItemRecipeInfo
{
	GENERATED_BODY()

	FItemRecipeInfo() : ItemID(0), CurrentQuantity(0), NeededQuantity(0), ItemName(FText()), ItemIcon(nullptr)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentQuantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 NeededQuantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ItemIcon;
};

UENUM(BlueprintType)
enum class ECraftingType : uint8 { ECT_PlayerInventory, ECT_CookingPot, ECT_CraftingBench, ECT_SmeltingForge, ECT_AdvancedWorkbench, ECT_StorageBox, ECT_CropPlot };

UCLASS()
class SURVIVAL_V3_API UCraftingSlot : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UCraftingSlot(const FObjectInitializer& Object);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> CraftingBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UTexture2D> ImageTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	bool bCanCraftItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 ItemID;

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
};
