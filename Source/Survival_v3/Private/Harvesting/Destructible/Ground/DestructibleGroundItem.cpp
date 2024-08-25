#include "Harvesting/Destructible/Ground/DestructibleGroundItem.h"
#include "Harvesting/Rock/Force/DestructionForce.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Kismet/GameplayStatics.h"

ADestructibleGroundItem::ADestructibleGroundItem() : SpawnTimer(8.0)
{
	GeometryCollection =  CreateDefaultSubobject<UGeometryCollectionComponent>(L"GeometryCollection");
}

void ADestructibleGroundItem::BeginPlay()
{
	Super::BeginPlay();

	if (DestructionForce = GetWorld()->SpawnActor<ADestructionForce>(DestructionForceClassRef, GetActorLocation(), FRotator(0, 0, 0)); IsValid(DestructionForce))
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ThisClass::OnSpawnFinished, SpawnTimer);
}

void ADestructibleGroundItem::HarvestFX() const
{
	UGameplayStatics::SpawnEmitterAtLocation(this, GroundParticleFX, GetActorLocation());

	UGameplayStatics::PlaySoundAtLocation(this, GroundItemBreakCue, GetActorLocation(), GetActorRotation(), 1, 1, 0, HarvestAttenuation);
}

void ADestructibleGroundItem::OnSpawnFinished()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);

	SpawnTimer = 8.0;

	HarvestFX();
	
	Destroy();
}
