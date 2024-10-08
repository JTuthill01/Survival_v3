#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "Structs/ItemsStructs/ItemStruct.h"
#include "Structs/Recipes/ItemRecipes.h"
#include "PlayerCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_V3_API IPlayerCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	class APlayerCharacter* GetPlayerRef();

	UFUNCTION(BlueprintNativeEvent)
	FRotator GetPlayerCameraRotation();

	UFUNCTION(BlueprintNativeEvent)
	FVector GetPlayerCameraLocation();

	UFUNCTION(BlueprintNativeEvent)
	void UpdateItem(EContainerType InType, int32 Index, FItemsStruct ItemInfo);

	UFUNCTION(BlueprintNativeEvent)
	void OnSlotDropped(EContainerType TargetContainer, EContainerType FromContainer, int32 FromIndex, int32 DroppedIndex, EArmourType ArmorType);

	UFUNCTION(BlueprintNativeEvent)
	void FirstPersonMontage(UAnimMontage* InMontage, class AHatchetMaster* EquipableItem);

	UFUNCTION(BlueprintNativeEvent)
	void HarvestItem(FItemsStruct Resource);

	UFUNCTION(BlueprintNativeEvent)
	void GetEndGramsAndItems(ECraftingType InType);
};
