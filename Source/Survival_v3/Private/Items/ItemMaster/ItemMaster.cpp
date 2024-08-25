#include "Items/ItemMaster/ItemMaster.h"

// Sets default values
AItemMaster::AItemMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AItemMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

