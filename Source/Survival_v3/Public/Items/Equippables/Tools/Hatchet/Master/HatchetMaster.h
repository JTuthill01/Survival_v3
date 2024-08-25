#pragma once

#include "CoreMinimal.h"
#include "Items/EquippableMaster/EquippableMaster.h"
#include "Structs/HarvestingStruct/HarvestingInfo.h"
#include "HatchetMaster.generated.h"

UCLASS()
class SURVIVAL_V3_API AHatchetMaster : public AEquippableMaster
{
	GENERATED_BODY()

public:
	AHatchetMaster();

#pragma region Interface Functions
	virtual void UseItem_Implementation(AActor* CharacterRef) override;

	virtual void EndAnimation_Implementation() override;

	virtual void NotifyInterface_Implementation() override;

#pragma endregion

protected:
	virtual void BeginPlay() override;

	virtual void HarvestFoliage(const double Damage, AActor* Actor);

	void CalculateResources(TArray<FResourceStructure> GivenResources, double LocalDamage);

	double GetPreferredToolTypeVariable(EHarvestingToolType InType);

	double GetToolTierVaraible(EToolTier InTier);

	double CustomMathExpression(double BaseVar, double RateVar, double ToolTypeVar, double ToolTierVar, double DamageVar);
	
	UPROPERTY()
	TObjectPtr<AActor> CharRef;

	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> HatchetRootComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables")
	TSoftObjectPtr<UAnimMontage> AnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables")
	EHarvestingToolType ToolType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables")
	EToolTier ToolTier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables")
	TObjectPtr<UParticleSystem> HatchetFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables")
	TObjectPtr<USoundBase> HatchetSFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables")
	TObjectPtr<USoundAttenuation> HatchetSoundAttenuation;

	double ItemDamage;

	bool bIsUsingItem;

private:
	void OnMontageLoadComplete();
};
