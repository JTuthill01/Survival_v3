#include "Harvesting/GroundItem/Master/GroundItemMaster.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "DataAssets/Harvesting/HarvestingResourceAsset.h"
#include "DataAssets/Primairy/ItemInfo.h"
#include "Harvesting/DestructibleMaster/DestructibleHarvestable.h"
#include "Interfaces/Character/Player/PlayerCharacterInterface.h"
#include "Inventory/Children/PlayerInventory/PlayerInventory.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Structs/ItemsStructs/ItemStruct.h"

AGroundItemMaster::AGroundItemMaster() : Health(50.0)
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(L"DefaultSceneRoot");
	SetRootComponent(DefaultSceneRoot);
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Base Mesh");
	BaseMesh->SetupAttachment(DefaultSceneRoot);
}

void AGroundItemMaster::InteractableFound_Implementation()
{
	
}

void AGroundItemMaster::InteractWithObject_Implementation()
{
	if (const double ResourceHealth = Health - 15.0; ResourceHealth <= 0.0)
	{
		if (auto&& LocalResource = Resources.LoadSynchronous(); IsValid(LocalResource))
		{
			AddResources(LocalResource->GivenItems);

			UGameplayStatics::PlaySoundAtLocation(this, HarvestSFX, GetActorLocation());
			
			const FTransform LocalTransform = GetTransform();
			
			if (const TSubclassOf<ADestructibleHarvestable> DestructibleHarvestableClassRef = LocalResource->DestructibleClass.LoadSynchronous(); IsValid(DestructibleHarvestableClassRef))
			{
				if (auto&& Spawned = GetWorld()->SpawnActor<ADestructibleHarvestable>(DestructibleHarvestableClassRef, LocalTransform); IsValid(Spawned))
					Destroy();
			}
		}
	}
	
	else
	{
		Health = ResourceHealth;

		UGameplayStatics::PlaySoundAtLocation(this, HarvestSFX, GetActorLocation());
		
		if (auto&& LoadedResource = Resources.LoadSynchronous(); IsValid(LoadedResource))
			AddResources(LoadedResource->GivenItems);
	}
}

void AGroundItemMaster::AddResources(TArray<FResourceStructure> GivenResourcesArray)
{
	for (const auto& GivenResources : GivenResourcesArray)
	{
		const double LocalRandom = UKismetMathLibrary::RandomFloatInRange(0.3, 1.2);
		
		if (const int32 LocalQuantity = UKismetMathLibrary::FTrunc(CustomHarvestGroundMathExpression(GivenResources.Quantity, 1.0, LocalRandom)); LocalQuantity > 0)
		{
			if (auto&& LocalResource = GivenResources.Resource.LoadSynchronous(); IsValid(LocalResource))
			{
				FItemsStruct LocalItemsStruct = FItemsStruct();

				LocalItemsStruct.ItemAsset = GivenResources.Resource;
				LocalItemsStruct.ItemID = LocalResource->ItemID;
				LocalItemsStruct.ItemQuantity = LocalQuantity;
				LocalItemsStruct.CurrentHP = LocalResource->ItemCurrentHP;
				LocalItemsStruct.MaxHP = LocalResource->ItemMaxHP;
				LocalItemsStruct.StackSize = LocalResource->StackSize;

				const TObjectPtr<APlayerCharacter> PlayerRef = IPlayerCharacterInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
				
				PlayerRef->GetPlayerInventory()->AddItem(LocalItemsStruct);

				if (const TObjectPtr<APlayerCharacterController> PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); IsValid(PC))
					IPlayerControllerInterface::Execute_ShowItemCollected(PC, LocalResource->ItemIcon, LocalItemsStruct.ItemQuantity, LocalResource->ItemName);
			}
		}
	}
}

double AGroundItemMaster::CustomHarvestGroundMathExpression(const double BaseVar, const double RateVar, const double RandomVar)
{
	const double Result = (BaseVar * RateVar) * RandomVar;

	return Result;
}

TSoftObjectPtr<UHarvestingResourceAsset> AGroundItemMaster::GetGivenResources_Implementation() { return Resources;}

void AGroundItemMaster::UpdateHealth_Implementation(const double InVal) { Health = InVal; }

double AGroundItemMaster::GetResourceHealth_Implementation(){ return Health; }
