#pragma once

#include "CoreMinimal.h"
#include "Harvesting/Master/HarvestingMaster.h"
#include "Interfaces/LargeItem/LargeItemInterface.h"
#include "LargeItemMaster.generated.h"

UCLASS()
class SURVIVAL_V3_API ALargeItemMaster : public AHarvestingMaster, public ILargeItemInterface
{
	GENERATED_BODY()

public:
	ALargeItemMaster();

#pragma region Interface Functions
	virtual TSoftObjectPtr<UHarvestingResourceAsset> GetLargeResources_Implementation() override;
	
	virtual double GetLargeItemHealth_Implementation() override;
	
	virtual void UpdateLargeItemHealth_Implementation(double Val) override;
#pragma endregion

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> ItemRootComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	double Health;
};
