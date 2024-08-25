#pragma once

#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "DestructionForce.generated.h"

UCLASS()
class SURVIVAL_V3_API ADestructionForce : public AFieldSystemActor
{
	GENERATED_BODY()

public:
	ADestructionForce();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class URadialFalloff> RadialFalloff;

protected:
	virtual void BeginPlay() override;

private:
	void OnTimerFinished();
	
	double DestructionForceTimer;

	FTimerHandle DestructionForceTimerHandle;
};
