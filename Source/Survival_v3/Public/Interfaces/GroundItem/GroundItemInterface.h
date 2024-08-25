#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GroundItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGroundItemInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_V3_API IGroundItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	double GetResourceHealth();

	UFUNCTION(BlueprintNativeEvent)
	void UpdateHealth(const double InVal);

	UFUNCTION(BlueprintNativeEvent)
	TSoftObjectPtr<class UHarvestingResourceAsset> GetGivenResources();
};
