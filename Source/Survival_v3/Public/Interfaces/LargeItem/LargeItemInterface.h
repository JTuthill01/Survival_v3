#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LargeItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULargeItemInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_V3_API ILargeItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	double GetLargeItemHealth();

	UFUNCTION(BlueprintNativeEvent)
	void UpdateLargeItemHealth(double Val);

	UFUNCTION(BlueprintNativeEvent)
	TSoftObjectPtr<class UHarvestingResourceAsset> GetLargeResources();
};
