#include "Harvesting/LargeItemMaster/LargeItemMaster.h"
#include "DataAssets/Harvesting/HarvestingResourceAsset.h"

ALargeItemMaster::ALargeItemMaster() : Health(50.0)
{
	ItemRootComponent = CreateDefaultSubobject<USceneComponent>(L"Item Root");
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Base Mesh");

	BaseMesh->SetupAttachment(ItemRootComponent);

	SetRootComponent(ItemRootComponent);
}

void ALargeItemMaster::UpdateLargeItemHealth_Implementation(double Val) { Health = Val; }

double ALargeItemMaster::GetLargeItemHealth_Implementation() { return Health; }

TSoftObjectPtr<UHarvestingResourceAsset> ALargeItemMaster::GetLargeResources_Implementation() { return Resources; }