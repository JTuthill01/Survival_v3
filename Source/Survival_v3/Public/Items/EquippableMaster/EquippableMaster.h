#pragma once

#include "CoreMinimal.h"
#include "Items/ItemMaster/ItemMaster.h"
#include "Interfaces/EquippableItem/EquippableItemInterface.h"
#include "EquippableMaster.generated.h"

UCLASS()
class SURVIVAL_V3_API AEquippableMaster : public AItemMaster, public IEquippableItemInterface
{
	GENERATED_BODY()

public:
	AEquippableMaster();

	virtual void GetEquippableInfo_Implementation(FName& OutSocketName, EEquippableState& OutState) override;

	virtual void UseItem_Implementation(AActor* CharacterRef) override;

	virtual void NotifyInterface_Implementation() override;

#pragma region Setters
	FORCEINLINE void SetSocketName(const FName InSocketName) { SocketName = InSocketName; }
	FORCEINLINE void SetAnimationState(const EEquippableState InState) { AnimationState = InState; }
#pragma endregion

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables")
	FName SocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables")
	EEquippableState AnimationState;
};
