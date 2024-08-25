#include "Items/Equippables/Tools/Hatchet/Master/HatchetMaster.h"
#include "Character/Player/PlayerCharacter.h"
#include "Interfaces/LargeItem/LargeItemInterface.h"
#include "DataAssets/Harvesting/HarvestingResourceAsset.h"
#include "DataAssets/Primairy/ItemInfo.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Harvesting/DestructibleMaster/DestructibleHarvestable.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AHatchetMaster::AHatchetMaster() : ToolType(EHarvestingToolType::EHTT_Pickaxe), ToolTier(EToolTier::ETT_Stone), ItemDamage(12.0), bIsUsingItem(false)
{
	HatchetRootComponent = CreateDefaultSubobject<USceneComponent>(L"Hatchet Root Component");
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Base Mesh");

	SetRootComponent(HatchetRootComponent);

	Mesh->SetupAttachment(HatchetRootComponent);
}

void AHatchetMaster::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = IPlayerCharacterInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AHatchetMaster::HarvestFoliage(const double Damage, AActor* Actor)
{
	//Damage = LocalDamage

	if (double LocalHealth = ILargeItemInterface::Execute_GetLargeItemHealth(Actor) - Damage; LocalHealth <= 0.0)
	{
		if (TSoftObjectPtr<UHarvestingResourceAsset> LocalResource = ILargeItemInterface::Execute_GetLargeResources(Actor).LoadSynchronous())
		{
			if (auto&& LoadedResource = LocalResource.LoadSynchronous(); IsValid(LoadedResource))
			{
				CalculateResources(LoadedResource->GivenItems, Damage);

				if (IsValid(Actor))
				{
					FTransform LocalTransform = Actor->GetTransform();

					Actor->Destroy();

					if (TSubclassOf<ADestructibleHarvestable> LoadedDestructible = LoadedResource->DestructibleClass.LoadSynchronous(); IsValid(LoadedDestructible))
					{
						auto&& Spawned = GetWorld()->SpawnActor<ADestructibleHarvestable>(LoadedDestructible, LocalTransform);

						if (IsValid(Spawned))
							Spawned->SetDirection(PlayerRef->GetActorForwardVector());
					}
				}
			}
		}
	}

	else
	{
		ILargeItemInterface::Execute_UpdateLargeItemHealth(Actor, LocalHealth);

		if (TSoftObjectPtr<UHarvestingResourceAsset> LocalResource = ILargeItemInterface::Execute_GetLargeResources(Actor).LoadSynchronous())
		{
			if (auto&& LoadedResource = LocalResource.LoadSynchronous(); IsValid(LoadedResource))
				CalculateResources(LoadedResource->GivenItems, Damage);
		}
	}
}

void AHatchetMaster::CalculateResources(TArray<FResourceStructure> GivenResources, double LocalDamage)
{
	//LocalDamage = NewLocalDamage

	for (int32 i = 0; i < GivenResources.Num(); ++i)
	{
		TSoftObjectPtr<UItemInfo> LocalResource = GivenResources[i].Resource;

		double ToolTypeVar = GetPreferredToolTypeVariable(GivenResources[i].PreferredTool);

		double ToolTierVar = GetToolTierVaraible(ToolTier);

		double ReturnQuantity = CustomMathExpression(GivenResources[i].Quantity, 1.0, ToolTypeVar, ToolTierVar, LocalDamage);
		
		if (int32 LocalResourceQuantity = UKismetMathLibrary::FTrunc(ReturnQuantity); LocalResourceQuantity > 0)
		{
			if (auto&& LoadedResource = LocalResource.LoadSynchronous(); IsValid(LoadedResource))
			{
				FItemsStruct LocalItems;

				LocalItems.ItemID = LoadedResource->ItemID;
				LocalItems.ItemQuantity = LocalResourceQuantity;
				LocalItems.ItemAsset = LocalResource;
				LocalItems.CurrentHP = LoadedResource->ItemCurrentHP;
				LocalItems.MaxHP = LoadedResource->ItemMaxHP;
				LocalItems.StackSize = LoadedResource->StackSize;
				
				IPlayerCharacterInterface::Execute_HarvestItem(PlayerRef, LocalItems);
			}
		}
	}
}

double AHatchetMaster::GetPreferredToolTypeVariable(const EHarvestingToolType InType)
{
	double LocalToolType;

	if (ToolType == InType)
		LocalToolType = UKismetMathLibrary::RandomFloatInRange(0.8, 1.1);

	else
		LocalToolType = UKismetMathLibrary::RandomFloatInRange(0.04, 0.5);

	return LocalToolType;
}

double AHatchetMaster::GetToolTierVaraible(const EToolTier InTier)
{
	double LocalTier = 0.0;

	switch (InTier)
	{
	case EToolTier::ETT_Stone:

		LocalTier = UKismetMathLibrary::RandomFloatInRange(0.8, 1.2);
		
		break;
		
	case EToolTier::ETT_Iron:

		LocalTier = UKismetMathLibrary::RandomFloatInRange(1.2, 1.8);
		
		break;

	default:
		break;
	}

	return LocalTier;
}

double AHatchetMaster::CustomMathExpression(const double BaseVar, const double RateVar, const double ToolTypeVar, const double ToolTierVar, const double DamageVar)
{
	const double Result = (BaseVar * RateVar) * (ToolTypeVar * ToolTierVar) * DamageVar;
	
	return Result;
}

void AHatchetMaster::UseItem_Implementation(AActor* CharacterRef)
{
	if (!bIsUsingItem)
	{
		bIsUsingItem = true;

		CharRef = CharacterRef;

		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

		TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(AnimMontage.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this,
			&ThisClass::OnMontageLoadComplete));
	}
}

void AHatchetMaster::OnMontageLoadComplete()
{
	if (IsValid(PlayerRef))
	{
		if (UAnimMontage* LocalMontage = Cast<UAnimMontage>(AnimMontage.Get()); IsValid(LocalMontage))
			IPlayerCharacterInterface::Execute_FirstPersonMontage(PlayerRef, LocalMontage, this);
	}
}

void AHatchetMaster::NotifyInterface_Implementation()
{
	FRotator LocalCamRotation = IPlayerCharacterInterface::Execute_GetPlayerCameraRotation(PlayerRef);

	FVector LocalCamLocation = IPlayerCharacterInterface::Execute_GetPlayerCameraLocation(PlayerRef);

	constexpr double LocalInteractDistance = 200.0;

	FVector End{(LocalCamRotation.Vector() * LocalInteractDistance) + LocalCamLocation};
	
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Emplace(this);
	ActorsToIgnore.Emplace(PlayerRef);

	FHitResult OutHit;

	const bool& bHasHitOccurred = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), LocalCamLocation, End, 20.F, UEngineTypes::ConvertToTraceType(ECC_Camera),
		true, ActorsToIgnore, EDrawDebugTrace::None, OutHit, true);

	if (bHasHitOccurred)
	{
		if (OutHit.GetActor()->GetClass()->ImplementsInterface(ULargeItemInterface::StaticClass()))
		{
			HarvestFoliage(ItemDamage, OutHit.GetActor());

			UGameplayStatics::SpawnEmitterAtLocation(this, HatchetFX, GetActorLocation());

			UGameplayStatics::PlaySoundAtLocation(this, HatchetSFX, GetActorLocation(), GetActorRotation(), 1, 1, 0, HatchetSoundAttenuation);
		}
	}
}

void AHatchetMaster::EndAnimation_Implementation() { bIsUsingItem = false; }

