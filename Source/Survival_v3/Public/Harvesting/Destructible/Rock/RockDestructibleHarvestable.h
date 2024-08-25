#pragma once

#include "CoreMinimal.h"
#include "Harvesting/DestructibleMaster/DestructibleHarvestable.h"
#include "RockDestructibleHarvestable.generated.h"

UCLASS()
class SURVIVAL_V3_API ARockDestructibleHarvestable : public ADestructibleHarvestable
{
	GENERATED_BODY()

public:
	ARockDestructibleHarvestable();

protected:
	virtual void BeginPlay() override;

	void OnSpawnFinished();

	void PlayFX() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UParticleSystem> ParticleFX;
	
private:
	UPROPERTY()
	TObjectPtr<class ADestructionForce> DestructionForce;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UGeometryCollectionComponent> GeometryCollection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ADestructionForce> DestructionForceClassRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundBase> RockBreakCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USoundAttenuation> HarvestAttenuation;

	double SpawnTimer;

	FTimerHandle SpawnTimerHandle;
};
