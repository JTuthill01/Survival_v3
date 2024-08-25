#include "Harvesting/Destructibles/Master/DestructibleTreeMaster.h"
#include "Components/CapsuleComponent.h"

ADestructibleTreeMaster::ADestructibleTreeMaster() : TreeTimer(15.0)
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComp = CreateDefaultSubobject<USceneComponent>(L"Root Component");
	SetRootComponent(RootComp);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(L"Capsule");
	Capsule->SetupAttachment(RootComp);
	Capsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Capsule->SetCollisionObjectType(ECC_PhysicsBody);
	Capsule->SetSimulatePhysics(true);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Base Mesh");
	BaseMesh->SetupAttachment(Capsule);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	Capsule_01 = CreateDefaultSubobject<UCapsuleComponent>(L"Capsule 01");
	Capsule_01->SetupAttachment(Capsule);
	Capsule_01->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Capsule_01->SetCollisionObjectType(ECC_PhysicsBody);

	Capsule_02 = CreateDefaultSubobject<UCapsuleComponent>(L"Capsule 02");
	Capsule_02->SetupAttachment(Capsule);
	Capsule_02->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Capsule_02->SetCollisionObjectType(ECC_PhysicsBody);

	Capsule_03 = CreateDefaultSubobject<UCapsuleComponent>(L"Capsule 03");
	Capsule_03->SetupAttachment(Capsule);
	Capsule_03->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Capsule_03->SetCollisionObjectType(ECC_PhysicsBody);

	Capsule_04 = CreateDefaultSubobject<UCapsuleComponent>(L"Capsule 04");
	Capsule_04->SetupAttachment(Capsule);
	Capsule_04->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	Capsule_04->SetCollisionObjectType(ECC_PhysicsBody);
}

void ADestructibleTreeMaster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADestructibleTreeMaster::BeginPlay()
{
	Super::BeginPlay();

	AddForce();
}

void ADestructibleTreeMaster::AddForce()
{
	if (IsValid(Capsule))
	{
		FVector NewForce{ Direction * 1'500.0 };
		
		Capsule->AddForce(NewForce, NAME_Name, true);

		GetWorldTimerManager().SetTimer(TreeHandle, this, &ThisClass::OnDestroyTree, TreeTimer);
	}
}

void ADestructibleTreeMaster::OnDestroyTree()
{
	GetWorldTimerManager().ClearTimer(TreeHandle);

	TreeTimer = 15.0;

	Destroy();
}
