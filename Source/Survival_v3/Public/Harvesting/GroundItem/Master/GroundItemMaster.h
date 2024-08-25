#pragma once

#include "CoreMinimal.h"
#include "Harvesting/Master/HarvestingMaster.h"
#include "Interfaces/GroundItem/GroundItemInterface.h"
#include "Interfaces/Interact/InteractInterface.h"
#include "Structs/HarvestingStruct/HarvestingInfo.h"
#include "GroundItemMaster.generated.h"

UCLASS()
class SURVIVAL_V3_API AGroundItemMaster : public AHarvestingMaster, public IGroundItemInterface, public IInteractInterface
{
	GENERATED_BODY()

public:
	AGroundItemMaster();

#pragma region Interface Functions
	virtual TSoftObjectPtr<UHarvestingResourceAsset> GetGivenResources_Implementation() override;
	
	virtual double GetResourceHealth_Implementation() override;
	
	virtual void UpdateHealth_Implementation(const double InVal) override;
	
	virtual void InteractableFound_Implementation() override;
	
	virtual void InteractWithObject_Implementation() override;
#pragma endregion

protected:
#pragma region Interact Functions

	void AddResources(TArray<FResourceStructure> GivenResourcesArray);

	double CustomHarvestGroundMathExpression(double BaseVar, double RateVar, double RandomVar);

#pragma endregion
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SFX")
	TObjectPtr<USoundBase> HarvestSFX;
	
	UPROPERTY(VisibleAnywhere)
	double Health;
};
