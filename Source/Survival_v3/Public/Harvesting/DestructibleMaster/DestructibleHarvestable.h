#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleHarvestable.generated.h"

UCLASS()
class SURVIVAL_V3_API ADestructibleHarvestable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleHarvestable();

	FORCEINLINE void SetDirection(const FVector& NewDirection) { Direction = NewDirection; }
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Direction;
};
