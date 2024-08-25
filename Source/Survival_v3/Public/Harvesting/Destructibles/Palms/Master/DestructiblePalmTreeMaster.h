#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Harvesting/Destructibles/Master/DestructibleTreeMaster.h"
#include "DestructiblePalmTreeMaster.generated.h"

UCLASS()
class SURVIVAL_V3_API ADestructiblePalmTreeMaster : public ADestructibleTreeMaster
{
	GENERATED_BODY()

public:
	ADestructiblePalmTreeMaster();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTimelineComponent> DissolveTimeline; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Materials")
	TObjectPtr<UMaterialInstanceDynamic> Mat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Curves")
	TObjectPtr<UCurveFloat> DissolveCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Materials")
	TObjectPtr<UMaterialInstance> SourceMaterial;

private:
	UFUNCTION()
	void OnDissolveStart();

	UFUNCTION()
	void OnDissolveEnd();
	
	void DissolveTimelineSetup();
	
	double DissolveDelayTimer;

	FTimerHandle DissolveDelayHandle;
};
