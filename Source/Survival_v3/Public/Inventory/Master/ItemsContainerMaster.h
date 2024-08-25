#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ItemsStructs/ItemStruct.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "ItemsContainerMaster.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL_V3_API UItemsContainerMaster : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemsContainerMaster();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Override in children classes
	virtual void HandleSlotDrop (const TObjectPtr<UItemsContainerMaster> FromContainer, const int32 FromIndex, const int32 DroppedIndex);

	virtual bool AddItemsToIndex(const FItemsStruct& ItemInfo, const int32 LocalSpecificIndex, const int32 LocalItemIndex);

	virtual bool RemoveItemAtIndex(const int32 IndexToRemove);

	void OnSlotDrop(const TObjectPtr<UItemsContainerMaster>& FromContainer, const int32 FromIndex, const int32 DroppedIndex);

	void FindEmptySlot(int32& LocalEmptySlotIndex, bool& bFoundEmptySlot);
	
	void AddItem(FItemsStruct Item, bool AddSplitItem = false);
	
	void TransferItem(const TObjectPtr<UItemsContainerMaster>& ToComponent, const int32 ToIndex, const int32 ItemIndexToTransfer);

	FItemsStruct GetItemAtIndex(const int32 Index);
	
	bool IsSlotEmpty(const int32 SlotIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Structs")
	TArray<FItemsStruct> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enums")
	EContainerType ContainerType;

private:
	void UpdateUI(int32 Index, const FItemsStruct& ItemInfo) const;

	bool HasItemsToStack(const FItemsStruct& ItemInfo);

	int32 SetTotalItemQuantity(const FItemsStruct& Item, const int32 Index);

	int32 SetTotalItemQuantity(const int32 Slot, const int32 Total, const int32 Max);

	int32 SetTotalItem(const int32 InTotalItemQuantity, const int32 InTempSlotQuantity, const int32 InMaxStackSize, const int32 InCurrentSlotQuantity);

	int32 SetCurrentSlotQuantity(const int32 CurrentSlot, const int32 TotalQuantity, const int32 MaxQuantity);

	int32 SetSlotQuantity(const int32 InSlotQuantity, const int32 InTotalItem, const int32 InMax);

	int32 CalcTotalItemQuantity(const int32 InTemp, const int32 InItemQuan, const int32 InMaxSize, const int32 InCurrent);
};
