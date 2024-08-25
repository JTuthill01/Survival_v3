#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "Structs/ItemsStructs/ItemStruct.h"
#include "PlayerControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_V3_API IPlayerControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void CloseInventory();

	UFUNCTION(BlueprintNativeEvent)
	void UpdateItemSlot(EContainerType InType, int32 Index, const FItemsStruct& ItemInfo);

	UFUNCTION(BlueprintNativeEvent)
	void ResetItemSlot(const EContainerType Container, const int32 Index);

	UFUNCTION(BlueprintNativeEvent)
	void ShowItemCollected(UTexture2D* InIcon, const int32 InResourceQuantity, const FText& InResourceName);
};
