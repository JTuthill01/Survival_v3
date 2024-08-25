#pragma once

#include "CoreMinimal.h"
#include "Harvesting/DestructibleMaster/DestructibleHarvestable.h"
#include "DestructibleTreeMaster.generated.h"

UCLASS()
class SURVIVAL_V3_API ADestructibleTreeMaster : public ADestructibleHarvestable
{
	GENERATED_BODY()

public:
	ADestructibleTreeMaster();

	virtual void Tick(float DeltaSeconds) override;

	void AddForce();

protected:
	virtual void BeginPlay() override;

#pragma region Components
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> RootComp;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCapsuleComponent> Capsule;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> Capsule_01;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> Capsule_02;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> Capsule_03;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> Capsule_04;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;
#pragma endregion

private:
	void OnDestroyTree();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	double TreeTimer;
	
	FTimerHandle TreeHandle;
};
