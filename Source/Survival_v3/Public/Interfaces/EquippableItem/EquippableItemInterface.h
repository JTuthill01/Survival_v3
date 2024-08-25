#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/EquippableState/EquippableState.h"
#include "EquippableItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEquippableItemInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_V3_API IEquippableItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void GetEquippableInfo(FName& OutSocketName, EEquippableState& OutState);

	UFUNCTION(BlueprintNativeEvent)
	void UseItem(AActor* CharacterRef);

	UFUNCTION(BlueprintNativeEvent)
	void EndAnimation();

	UFUNCTION(BlueprintNativeEvent)
	void NotifyInterface();
};
