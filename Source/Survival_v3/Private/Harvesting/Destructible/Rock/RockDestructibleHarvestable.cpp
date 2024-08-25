#include "Harvesting/Destructible/Rock/RockDestructibleHarvestable.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Harvesting/Rock/Force/DestructionForce.h"
#include "Kismet/GameplayStatics.h"

ARockDestructibleHarvestable::ARockDestructibleHarvestable() : SpawnTimer(8.0)
{
	GeometryCollection =  CreateDefaultSubobject<UGeometryCollectionComponent>(L"GeometryCollection");
}

void ARockDestructibleHarvestable::BeginPlay()
{
	Super::BeginPlay();

	DestructionForce = GetWorld()->SpawnActor<ADestructionForce>(DestructionForceClassRef, GetActorLocation(), FRotator(0, 0, 0));

	if (IsValid(DestructionForce))
	{
		PlayFX();
		
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ThisClass::OnSpawnFinished, SpawnTimer, false);
	}
}

void ARockDestructibleHarvestable::OnSpawnFinished()
{
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

	SpawnTimer = 8.0;

	Destroy();
}

void ARockDestructibleHarvestable::PlayFX() const
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleFX, GetActorLocation());

	UGameplayStatics::PlaySoundAtLocation(this, RockBreakCue, GetActorLocation(), GetActorRotation(), 1, 1, 0, HarvestAttenuation);
}
