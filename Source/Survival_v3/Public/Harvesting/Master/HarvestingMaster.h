#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HarvestingMaster.generated.h"

UCLASS()
class SURVIVAL_V3_API AHarvestingMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHarvestingMaster();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources")
	TSoftObjectPtr<class UHarvestingResourceAsset> Resources;
};
