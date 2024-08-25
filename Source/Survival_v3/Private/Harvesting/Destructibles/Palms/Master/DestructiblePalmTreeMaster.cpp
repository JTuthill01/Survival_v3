#include "Harvesting/Destructibles/Palms/Master/DestructiblePalmTreeMaster.h"
#include "Components/TimelineComponent.h"

ADestructiblePalmTreeMaster::ADestructiblePalmTreeMaster() : DissolveDelayTimer(10.0)
{
	PrimaryActorTick.bCanEverTick = true;

	DissolveTimeline = CreateDefaultSubobject<UTimelineComponent>(L"Dissolve Timeline");
}

void ADestructiblePalmTreeMaster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsValid(DissolveTimeline))
		DissolveTimeline->TickComponent(DeltaSeconds, LEVELTICK_TimeOnly, nullptr);
}

void ADestructiblePalmTreeMaster::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DissolveDelayHandle, this, &ThisClass::DissolveTimelineSetup, DissolveDelayTimer);

	Mat = BaseMesh->CreateDynamicMaterialInstance(0, SourceMaterial);
}

void ADestructiblePalmTreeMaster::DissolveTimelineSetup()
{
	if (IsValid(DissolveCurve))
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("OnDissolveStart"));

		TimelineFinishedCallback.BindUFunction(this, FName("OnDissolveEnd"));

		DissolveTimeline->AddInterpFloat(DissolveCurve, TimelineCallback);
		DissolveTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);
		DissolveTimeline->PlayFromStart();
	}
}

void ADestructiblePalmTreeMaster::OnDissolveStart()
{
	Mat->SetScalarParameterValue(FName("Dissolve"), DissolveCurve->GetFloatValue(DissolveTimeline->GetPlaybackPosition()));
}

void ADestructiblePalmTreeMaster::OnDissolveEnd()
{
	BaseMesh->SetCastShadow(false);
	
	BaseMesh->SetHiddenInGame(true);
	
	GetWorldTimerManager().ClearTimer(DissolveDelayHandle);

	DissolveDelayTimer = 10.0;
}
