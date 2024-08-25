#include "Harvesting/Master/HarvestingMaster.h"

// Sets default values
AHarvestingMaster::AHarvestingMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AHarvestingMaster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHarvestingMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

