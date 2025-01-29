#include "Character/Player/PlayerCharacter.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Inventory/Children/PlayerInventory/PlayerInventory.h"
#include "Inventory/Children/Hotbar/PlayerHotbar.h"
#include "Inventory/Master/ItemsContainerMaster.h"
#include "Items/Equippables/Tools/Hatchet/Master/HatchetMaster.h"
#include "Enums/ItemEnums/ItemEnums.h"
#include "DataAssets/Primairy/ItemInfo.h"
#include "Interfaces/GroundItem/GroundItemInterface.h"
#include "Interfaces/Interact/InteractInterface.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/AssetManager.h"

// Sets default values
APlayerCharacter::APlayerCharacter() : EquippedState(EEquippableState::ES_Default), bIsUsingItem(false), bIsHarvesting(false), bIsCrafting(false), MontageTimer(0.0), InteractTimer(0.25),
	AddCraftedItemTimer(3.0)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(Camera);
	Arms->SetCastShadow(false);

	PlayerInventory = CreateDefaultSubobject<UPlayerInventory>(L"Player Inventory Component");

	PlayerHotbar = CreateDefaultSubobject<UPlayerHotbar>(L"Player Hotbar Component");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(InteractTimerHandle, this, &ThisClass::ScanForInteractable, InteractTimer, true);
}

// Called every frame
void APlayerCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::InventoryDebug()
{
	if (IsValid(PlayerInventory))
		PlayerInventory->AddItem(DebugStruct);
}

TObjectPtr<UItemsContainerMaster> APlayerCharacter::SetContainerType(const EContainerType InContainerType) const
{
	TObjectPtr<UItemsContainerMaster> LocalContainer = nullptr;

	switch (InContainerType)
	{
	case EContainerType::ECT_Inventory:

		LocalContainer = PlayerInventory;
		
		break;

	case EContainerType::ECT_HotBar:

		LocalContainer = PlayerHotbar;
		
		break;
		
	case EContainerType::ECT_Storage:
		break;
		
	case EContainerType::ECT_Armour:
		break;
		
	default:
		break;
	}

	return LocalContainer;
}

TObjectPtr<UItemsContainerMaster> APlayerCharacter::SetContainerType(ECraftingType InContainerType) const
{
	TObjectPtr<UItemsContainerMaster> LocalContainer = nullptr;

	switch (InContainerType)
	{
	case ECraftingType::ECT_PlayerInventory:

		LocalContainer = PlayerInventory;
		
		break;
	case ECraftingType::ECT_CookingPot:
		break;
		
	case ECraftingType::ECT_CraftingBench:
		break;
		
	case ECraftingType::ECT_SmeltingForge:
		break;
		
	case ECraftingType::ECT_AdvancedWorkbench:
		break;
		
	case ECraftingType::ECT_StorageBox:
		break;
		
	case ECraftingType::ECT_CropPlot:
		break;
		
	default:
		break;
	}

	return LocalContainer;
}

//Update Item Slots Icons 
void APlayerCharacter::UpdateItem_Implementation(const EContainerType InType, const int32 Index, const FItemsStruct ItemInfo)
{
	if (const TObjectPtr<APlayerCharacterController> PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); IsValid(PC))
		IPlayerControllerInterface::Execute_UpdateItemSlot(PC, InType, Index, ItemInfo);
}

void APlayerCharacter::OnSlotDropped_Implementation(const EContainerType TargetContainer, const EContainerType FromContainer, const int32 FromIndex, const int32 DroppedIndex,
	EArmourType ArmorType)
{
	TObjectPtr<UItemsContainerMaster> LocalContainer;

	switch (TargetContainer)
	{
	case EContainerType::ECT_Inventory:

		LocalContainer = SetContainerType(FromContainer);
		
		if (IsValid(LocalContainer) && IsValid(PlayerInventory))
			LocalContainer->OnSlotDrop(LocalContainer, FromIndex, DroppedIndex);

		break;
		
	case EContainerType::ECT_HotBar:

		LocalContainer = SetContainerType(FromContainer);
		
		if (IsValid(LocalContainer) && IsValid(PlayerHotbar))
			LocalContainer->OnSlotDrop(LocalContainer, FromIndex, DroppedIndex);
		
		break;
		
	case EContainerType::ECT_Storage:
		break;
		
	case EContainerType::ECT_Armour:
		break;

	default:
		break;
	}
}

void APlayerCharacter::FirstPersonMontage_Implementation(UAnimMontage* InMontage, AHatchetMaster* EquipableItem)
{
	bIsUsingItem = true;

	EquippedItem = EquipableItem;
	
	if (TObjectPtr<UAnimInstance> PlayerAnim = Arms->GetAnimInstance(); IsValid(PlayerAnim))
	{
		MontageTimer = PlayerAnim->Montage_Play(InMontage);

		GetWorldTimerManager().SetTimer(MontageTimerHandle, this, &APlayerCharacter::OnPlayerMontageComplete, MontageTimer);
	}
}

void APlayerCharacter::HarvestItem_Implementation(FItemsStruct Resource)
{
	if (IsValid(PlayerInventory))
	{
		PlayerInventory->AddItem(Resource);

		if (const TObjectPtr<UItemInfo> LocalResource = Resource.ItemAsset.LoadSynchronous(); IsValid(LocalResource))
		{
			if (const TObjectPtr<APlayerCharacterController> PC = Cast<APlayerCharacterController>(GetController()); IsValid(PC))
				IPlayerControllerInterface::Execute_ShowItemCollected(PC, LocalResource->ItemIcon, Resource.ItemQuantity, LocalResource->ItemName);
		}
	}
}

void APlayerCharacter::GetEndGramsAndItems_Implementation(ECraftingType InType)
{
	switch (InType)
	{
	case ECraftingType::ECT_PlayerInventory:
		
		if (const TObjectPtr<APlayerCharacterController> PC = Cast<APlayerCharacterController>(GetController()); IsValid(PC))
		{
			PC->SetupCraftableItem(InType, PlayerInventory->GetItemQuantities());
		}
		
		break;
		
	case ECraftingType::ECT_CookingPot:
		break;
		
	case ECraftingType::ECT_CraftingBench:
		break;
		
	case ECraftingType::ECT_SmeltingForge:
		break;
		
	case ECraftingType::ECT_AdvancedWorkbench:
		break;
		
	case ECraftingType::ECT_StorageBox:
		break;
		
	case ECraftingType::ECT_CropPlot:
		break;

	default:
		break;
	}
}

void APlayerCharacter::CraftItems(TSoftObjectPtr<UItemRecipe> Recipe, EContainerType ContainerType, ECraftingType CraftType)
{
	IPlayerCharacterInterface::CraftItems(Recipe, ContainerType, CraftType);
}

void APlayerCharacter::OnPlayerMontageComplete()
{
	MontageTimer = 0.0;

	GetWorldTimerManager().ClearTimer(MontageTimerHandle);

	if (IsValid(EquippedItem))
	{
		IEquippableItemInterface::Execute_EndAnimation(EquippedItem);

		bIsUsingItem = false;
	}

	bIsUsingItem = false;
}

void APlayerCharacter::OnAddCraftedItemComplete(UItemInfo* LoadedItemToAdd, TSoftObjectPtr<UItemInfo> OutInfo, EContainerType LoadedContainer, ECraftingType LoadedCraftingType)
{
	GetWorldTimerManager().SetTimer(AddCraftedItemHandle, [&]() { this->AddCraftedItem(LoadedItemToAdd, OutInfo, LoadedContainer, LoadedCraftingType); },
		AddCraftedItemTimer, false);
}

void APlayerCharacter::ScanForInteractable()
{
	const FVector Start = Camera->GetComponentLocation();
	const FVector End = Start + (Camera->GetComponentRotation().Vector() * 400.F);

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(this);
	
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	if (FHitResult HitResult; UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TraceObjects, true, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true))
	{
		if (HitResult.GetActor())
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
				IInteractInterface::Execute_InteractableFound(HitResult.GetActor());
		}
	}
	
	else
		OnClearViewport.Broadcast();
}

bool APlayerCharacter::CheckIfCanCraftItem(int32 ID, EContainerType CraftContainerType, ECraftingType TableType)
{

	return false;
}

void APlayerCharacter::InteractWithObject()
{
	if (!bIsHarvesting)
	{
		bIsHarvesting = true;
		const FVector Start = Camera->GetComponentLocation();
		const FVector End = Start + (Camera->GetComponentRotation().Vector() * 400.F);

		TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
		TArray<AActor*> ActorsToIgnore;

		ActorsToIgnore.Add(this);

		TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
		
		if (FHitResult HitResult; UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TraceObjects, true, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true))
		{
			if (HitResult.GetActor())
			{
				if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
				{
					if (HitResult.GetActor()->GetClass()->ImplementsInterface(UGroundItemInterface::StaticClass()))
					{
						if (IsValid(EquippedItem))
						{
							IInteractInterface::Execute_InteractWithObject(HitResult.GetActor());
							
							bIsHarvesting = false;
						}

						else
						{
							IInteractInterface::Execute_InteractWithObject(HitResult.GetActor());
							
							Arms->GetAnimInstance()->Montage_Play(PlayerHarvestMontage);

							bIsHarvesting = false;
						}
					}

					else
						IInteractInterface::Execute_InteractWithObject(HitResult.GetActor());
				}
			}

			else
				bIsHarvesting = false;
		}

		else
			bIsHarvesting = false;
	}
}

void APlayerCharacter::CraftItem(TSoftObjectPtr<UItemRecipe> RecipeAsset, EContainerType Type, ECraftingType CraftType)
{
	if (bool bHasAdminMode = false; !bHasAdminMode)
	{
		if (bIsCrafting = false; !bIsCrafting)
		{
			bIsCrafting = true;

			FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

			FSoftObjectPath Path = RecipeAsset.ToSoftObjectPath();

			TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(Path, FStreamableDelegate::CreateUObject(this, &ThisClass::CraftedItem,
				RecipeAsset, Type, CraftType));
		}
	}
}

TSoftObjectPtr<UItemInfo> APlayerCharacter::FCraftItem(bool& CanCraft, EContainerType& ContainerToAdd, ECraftingType& CraftTableType, TObjectPtr<UItemRecipe> RecipeAsset,
	EContainerType Type, ECraftingType CraftType) const
{
	if (TObjectPtr<UItemsContainerMaster> LocalContainer = SetContainerType(CraftType); IsValid(LocalContainer))
	{
		CanCraft = LocalContainer->CheckIfCraftable(RecipeAsset->RequiredItems);

		ContainerToAdd = Type;

		CraftTableType = CraftType;

		return RecipeAsset->ItemAsset;
	}

	return nullptr;
}

void APlayerCharacter::CraftedItem(TSoftObjectPtr<UItemRecipe> RecipeAsset, EContainerType Type, ECraftingType CraftType)
{
	bool bLocalCanCraft;

	EContainerType LocalContainerToAdd;

	ECraftingType LocalCraftTableType;
	
	if (const TObjectPtr<UItemRecipe> Recipe = Cast<UItemRecipe>(RecipeAsset.Get()); IsValid(Recipe))
	{
		FCraftItem(bLocalCanCraft, LocalContainerToAdd, LocalCraftTableType, Recipe, Type, CraftType);

		if (!bLocalCanCraft)
			bIsCrafting = false;

		else if (bLocalCanCraft)
		{
			FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

			FSoftObjectPath Path = RecipeAsset.ToSoftObjectPath();

			TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(Path, FStreamableDelegate::CreateUObject(this, &ThisClass::OnAddCraftedItemComplete,
				Recipe->ItemAsset.Get(), Recipe->ItemAsset , Type, CraftType));
		}
	}
}

void APlayerCharacter::AddCraftedItem(UItemInfo* ItemToAdd, TSoftObjectPtr<UItemInfo> InInfo, EContainerType AddedContainer, ECraftingType AddCraftingType)
{
	GetWorldTimerManager().ClearTimer(AddCraftedItemHandle);

	if (auto&& LocalInventory = SetContainerType(AddedContainer); IsValid(LocalInventory))
	{
		FItemsStruct LocalItemStruct = FItemsStruct();

		LocalItemStruct.ItemID = ItemToAdd->ItemID;
		LocalItemStruct.ItemQuantity = 1;
		LocalItemStruct.ItemAsset = InInfo;
		LocalItemStruct.CurrentHP = ItemToAdd->ItemCurrentHP;
		LocalItemStruct.MaxHP = ItemToAdd->ItemMaxHP;
		LocalItemStruct.CurrentAmmo = ItemToAdd->CurrentAmmo;
		LocalItemStruct.MaxAmmo = ItemToAdd->MaxAmmo;
		LocalItemStruct.StackSize = ItemToAdd->StackSize;
		
		LocalInventory->AddItem(LocalItemStruct);

		switch (AddCraftingType)
		{
		case ECraftingType::ECT_PlayerInventory:
			break;
			
		case ECraftingType::ECT_CookingPot:
			break;
			
		case ECraftingType::ECT_CraftingBench:
			break;
			
		case ECraftingType::ECT_SmeltingForge:
			break;
			
		case ECraftingType::ECT_AdvancedWorkbench:
			break;
			
		case ECraftingType::ECT_StorageBox:
			break;
			
		case ECraftingType::ECT_CropPlot:
			break;

		default:
			break;
		}
	}
}

APlayerCharacter* APlayerCharacter::GetPlayerRef_Implementation() { return this; }

FRotator APlayerCharacter::GetPlayerCameraRotation_Implementation() { return Camera->GetComponentRotation(); }

FVector APlayerCharacter::GetPlayerCameraLocation_Implementation() { return Camera->GetComponentLocation(); }

