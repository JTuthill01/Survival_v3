#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/HarvestingStruct/HarvestingInfo.h"
#include "HarvestingResourceAsset.generated.h"

UCLASS()
class SURVIVAL_V3_API UHarvestingResourceAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UHarvestingResourceAsset();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	TArray<FResourceStructure> GivenItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	TSoftClassPtr<class ADestructibleHarvestable> DestructibleClass;
};
