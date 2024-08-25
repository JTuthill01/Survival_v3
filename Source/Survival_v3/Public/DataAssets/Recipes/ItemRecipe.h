#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/Crafting/ItemRecipeStruct.h"
#include "ItemRecipe.generated.h"

UCLASS()
class SURVIVAL_V3_API UItemRecipe : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UItemRecipe();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	FText ItemName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	int32 ItemExperience;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	TSoftObjectPtr<class UItemInfo> ItemAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	TArray<FItemRecipeStruct> RequiredItems;
};
