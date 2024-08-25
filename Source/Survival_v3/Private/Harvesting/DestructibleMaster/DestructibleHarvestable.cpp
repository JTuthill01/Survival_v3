#include "Harvesting/DestructibleMaster/DestructibleHarvestable.h"

// Sets default values
ADestructibleHarvestable::ADestructibleHarvestable() : Direction(FVector::Zero())
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADestructibleHarvestable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADestructibleHarvestable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

