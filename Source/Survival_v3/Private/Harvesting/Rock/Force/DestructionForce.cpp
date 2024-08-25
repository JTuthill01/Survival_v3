#include "Harvesting/Rock/Force/DestructionForce.h"
#include "Components/SphereComponent.h"
#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"

ADestructionForce::ADestructionForce() : DestructionForceTimer(2.0)
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(L"SphereComponent");
	SphereComponent->SetupAttachment(GetRootComponent());

	RadialFalloff = CreateDefaultSubobject<URadialFalloff>(L"RadialFalloff");
}

void ADestructionForce::BeginPlay()
{
	Super::BeginPlay();

	auto&& Radial = RadialFalloff->SetRadialFalloff(50'000.F, 0.F, 1.F, 0.F, SphereComponent->GetScaledSphereRadius(),
		SphereComponent->GetComponentLocation(), Field_FallOff_None);

	FieldSystemComponent->ApplyPhysicsField(true, Field_ExternalClusterStrain, nullptr, Radial);

	GetWorldTimerManager().SetTimer(DestructionForceTimerHandle, this, &ThisClass::OnTimerFinished, DestructionForceTimer, false);
}

void ADestructionForce::OnTimerFinished()
{
	GetWorldTimerManager().ClearTimer(DestructionForceTimerHandle);

	DestructionForceTimer = 2.0;
	
	Destroy();
}
