#pragma once

#include "CoreMinimal.h"
#include "Harvesting/DestructibleMaster/DestructibleHarvestable.h"
#include "DestructibleGroundItem.generated.h"

UCLASS()
class SURVIVAL_V3_API ADestructibleGroundItem : public ADestructibleHarvestable
{
	GENERATED_BODY()

public:
	ADestructibleGroundItem();

protected:
	virtual void BeginPlay() override;

	void HarvestFX() const;

	UPROPERTY()
	TObjectPtr<class ADestructionForce> DestructionForce;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UGeometryCollectionComponent> GeometryCollection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ADestructionForce> DestructionForceClassRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UParticleSystem> GroundParticleFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
	TObjectPtr<USoundBase> GroundItemBreakCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
	TObjectPtr<USoundAttenuation> HarvestAttenuation;

private:
	void OnSpawnFinished();
	
	double SpawnTimer;

	FTimerHandle SpawnTimerHandle;
};
