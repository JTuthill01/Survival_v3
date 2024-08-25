#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Enums/EquippableState/EquippableState.h"
#include "Interfaces/Character/Controller/PlayerControllerInterface.h"
#include "PlayerCharacterController.generated.h"

struct FStreamableHandle;
struct FStreamableManager;
class UInputAction;

UCLASS()
class SURVIVAL_V3_API APlayerCharacterController : public APlayerController, public IPlayerControllerInterface
{
	GENERATED_BODY()

public:
	APlayerCharacterController();

	virtual void SetupInputComponent() override;

#pragma region Interface Functions
	virtual void CloseInventory_Implementation() override;

	virtual void UpdateItemSlot_Implementation(EContainerType InType, int32 Index, const FItemsStruct& ItemInfo) override;

	virtual void ResetItemSlot_Implementation(const EContainerType Container, const int32 Index) override;

	virtual void ShowItemCollected_Implementation(UTexture2D* InIcon, const int32 InResourceQuantity, const FText& InResourceName) override;
#pragma endregion

protected:

	virtual void BeginPlay() override;

#pragma region INPUT

	//Input Actions//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> InventoryAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> Hotbar01Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> Hotbar02Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> Hotbar03Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> Hotbar04Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> Hotbar05Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> Hotbar06Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> Hotbar07Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> Hotbar08Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> InteractAction;

	//Mapping Contexts//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InputMappings)
	TObjectPtr<class UInputMappingContext> BaseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InputMappings)
	int32 BaseMappingPriority = 0;

	//Input Functions//
	void OnHotBar(const FInputActionValue& Value, int32 Index);
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void StopJump();
	void OpenCloseInventory();
	void Attack();
	void Interact();
	
#pragma endregion

	void InitializeInventoryWidget();

#pragma region Debug

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> DebugAction;

	void DebugKey();
	
#pragma endregion

private:
#pragma region Private Functions
	class UInventorySlot* GetInventoryWidget(EContainerType Container, int32 SlotIndex) const;

	void SpawnEquipableItem(TSubclassOf<AActor> Class, int32 EquippedIndex);

	void EquipItem(const TObjectPtr<AActor>& Target, FName SocketName, EEquippableState EquippedState);
#pragma endregion

	UPROPERTY()
	TObjectPtr<AActor> EquippedItemRef = nullptr;
	
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

	UPROPERTY()
	TObjectPtr<class UMainUILayout> RootLayout;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMainUILayout> MainUISubclass;

	int32 HotBarIndex;
	int32 IndexEquipped;

	bool bIsInventoryShown;
	bool bIsUsingItem;

	FItemsStruct LoadedItems;
};
