#pragma once

#include "CoreMinimal.h"
#include "Enums/EquippableState/EquippableState.h"
#include "GameFramework/Character.h"
#include "Interfaces/Character/Player/PlayerCharacterInterface.h"
#include "PlayerCharacter.generated.h"

class UItemsContainerMaster;
class UPlayerInventory;
class UPlayerHotbar;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClearViewport);

UCLASS()
class SURVIVAL_V3_API APlayerCharacter : public ACharacter, public IPlayerCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	FORCEINLINE TObjectPtr<UPlayerInventory> GetPlayerInventory() const { return PlayerInventory; }
	FORCEINLINE TObjectPtr<UPlayerHotbar> GetPlayerHotbar() const { return PlayerHotbar; }
	FORCEINLINE TObjectPtr<USkeletalMeshComponent> GetPlayerArms() const { return Arms; }
	FORCEINLINE TObjectPtr<AHatchetMaster> GetEquippedItem() const { return EquippedItem; }
	FORCEINLINE FItemsStruct GetDebugStruct() const { return DebugStruct; }

	FORCEINLINE void SetState(EEquippableState NewState) { EquippedState = NewState; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

#pragma region Interface Functions
	virtual APlayerCharacter* GetPlayerRef_Implementation() override;

	virtual FRotator GetPlayerCameraRotation_Implementation() override;

	virtual FVector GetPlayerCameraLocation_Implementation() override;

	virtual void UpdateItem_Implementation(EContainerType InType, int32 Index, FItemsStruct ItemInfo) override;

	virtual void OnSlotDropped_Implementation(EContainerType TargetContainer, EContainerType FromContainer, int32 FromIndex, int32 DroppedIndex, EArmourType ArmorType) override;

	virtual void FirstPersonMontage_Implementation(UAnimMontage* InMontage, AHatchetMaster* EquipableItem) override;

	virtual void HarvestItem_Implementation(FItemsStruct Resource) override;

	virtual void GetEndGramsAndItems_Implementation(ECraftingType InType) override;
#pragma endregion

	void InteractWithObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintAssignable)
	FOnClearViewport OnClearViewport;
	
#pragma region Inventory Debug
	void InventoryDebug();
#pragma endregion

private:
#pragma region Private Function
	TObjectPtr<UItemsContainerMaster> SetContainerType(EContainerType InContainerType) const;

	void OnPlayerMontageComplete();

	void ScanForInteractable();

#pragma endregion

#pragma region UPROPERTY Variables
	UPROPERTY()
	TObjectPtr<AHatchetMaster> EquippedItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DebugStuff, meta = (AllowPrivateAccess = "true"))
	FItemsStruct DebugStruct;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SK_Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Arms;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Montages, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> PlayerHarvestMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerInventory> PlayerInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerHotbar> PlayerHotbar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enums, meta = (AllowPrivateAccess = "true"))
	EEquippableState EquippedState;
#pragma endregion

	bool bIsUsingItem;
	bool bIsHarvesting;

	double MontageTimer;
	double InteractTimer;

	FTimerHandle MontageTimerHandle;
	FTimerHandle InteractTimerHandle;
};
