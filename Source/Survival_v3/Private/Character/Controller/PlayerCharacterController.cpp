#include "Character/Controller/PlayerCharacterController.h"
#include "Character/Player/PlayerCharacter.h"
#include "Inventory/Children/Hotbar/PlayerHotbar.h"
#include "UI/Widgets/Main/MainUILayout.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Primairy/ItemInfo.h"
#include "GameFramework/Character.h"
#include "Items/EquippableMaster/EquippableMaster.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/Grid/ItemContainerGrid.h"
#include "UI/Widgets/Hotbar/HotbarWidget.h"
#include "UI/Widgets/HUD/DefaultHUDLayout.h"
#include "UI/Widgets/Inventory/InventoryWidget.h"
#include "UI/Widgets/InventoryLayout/GameInventoryLayout.h"
#include "UI/Widgets/PlayerWidgets/ItemCollected/ItemCollectedWidget.h"
#include "UI/Widgets/Slot/InventorySlot.h"

APlayerCharacterController::APlayerCharacterController() : HotBarIndex(0), IndexEquipped(0), bIsInventoryShown(false), bIsUsingItem(false), LoadedItems(FItemsStruct())
{
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	RootLayout = CreateWidget<UMainUILayout>(this, MainUISubclass);

	if (IsValid(RootLayout))
	{
		RootLayout->AddToViewport();

		RootLayout->PushDefaultHUDLayout();

		InitializeInventoryWidget();
	}
}

void APlayerCharacterController::InitializeInventoryWidget()
{
	if (IsValid(RootLayout))
	{
		RootLayout->PushGameInventoryLayout();

		bIsInventoryShown = true;

		if (IsValid(RootLayout->GameInventoryLayout))
			RootLayout->GameInventoryLayout->DeactivateWidget();
	}
}

void APlayerCharacterController::UpdateItemSlot_Implementation(const EContainerType InType, const int32 Index, const FItemsStruct& ItemInfo)
{
	if(const TObjectPtr<UInventorySlot> Slot = GetInventoryWidget(InType, Index); IsValid(Slot))
		Slot->UpdateSlot(ItemInfo);
}

void APlayerCharacterController::ResetItemSlot_Implementation(const EContainerType Container, const int32 Index)
{
	if(const TObjectPtr<UInventorySlot> Slot = GetInventoryWidget(Container, Index); IsValid(Slot))
		Slot->ResetInventorySlot();
}

void APlayerCharacterController::ShowItemCollected_Implementation(UTexture2D* InIcon, const int32 InResourceQuantity, const FText& InResourceName)
{
	RootLayout->DefaultHUDLayout->AddResources(InIcon, InResourceQuantity, InResourceName);

	RootLayout->DefaultHUDLayout->GetItemCollectedWidget()->OnResourceTextBlockChange.Broadcast(InResourceQuantity, InResourceName);
}

void APlayerCharacterController::SetupCraftableItem(ECraftingType InCraftingType, const TArray<FSimpleItemStruct>& Item)
{
	RootLayout->GameInventoryLayout->UpdateCraftWidget(InCraftingType, Item);
}

void APlayerCharacterController::ShowCraftItemTooltip(const TObjectPtr<UTexture2D>& ItemIcon, const FText& ItemName, TArray<FItemRecipeInfo> RequiredItems, TSoftObjectPtr<UItemRecipe> ItemAsset)
{
	if (IsValid(RootLayout))
	{
		if (IsValid(RootLayout->GameInventoryLayout))
			RootLayout->GameInventoryLayout->ShowCraftTooltip(ItemIcon,RequiredItems, ItemName, ItemAsset);
	}
}

UInventorySlot* APlayerCharacterController::GetInventoryWidget(EContainerType Container, int32 SlotIndex) const
{
	TObjectPtr<UInventorySlot> LocalSlot;
	
	switch (Container)
	{
	case EContainerType::ECT_Inventory:

		if (IsValid(RootLayout))
			LocalSlot = RootLayout->GameInventoryLayout->WBP_Inventory->WBP_ItemContainerGrid->GetSlots()[SlotIndex];

		break;
		
	case EContainerType::ECT_HotBar:
		
		if (IsValid(RootLayout))
			LocalSlot = RootLayout->DefaultHUDLayout->WBP_Hotbar->ItemContainerGrid->GetSlots()[SlotIndex];
		
		break;
		
	case EContainerType::ECT_Storage:
		break;
		
	case EContainerType::ECT_Armour:
		break;

	default:
		break;
	}

	return LocalSlot;
}

void APlayerCharacterController::SpawnEquipableItem(TSubclassOf<AActor> Class, int32 EquippedIndex)
{
	IndexEquipped = EquippedIndex;
	
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	EquippedItemRef = GetWorld()->SpawnActor<AEquippableMaster>(Class, Params);

	if (IsValid(EquippedItemRef))
	{
		EquippedItemRef->SetOwner(PlayerRef);

		FName LocalName;

		EEquippableState LocalState;

		IEquippableItemInterface::Execute_GetEquippableInfo(EquippedItemRef, LocalName, LocalState);

		EquipItem(EquippedItemRef, LocalName, LocalState);
	}
}

void APlayerCharacterController::EquipItem(const TObjectPtr<AActor>& Target, FName SocketName, EEquippableState EquippedState)
{
	if (IsValid(Target))
	{
		Target->AttachToComponent(PlayerRef->GetPlayerArms(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);

		PlayerRef->SetState(EquippedState);
	}
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
		Subsystem->ClearAllMappings();

		// Add each mapping context, along with their priority values. Higher values out prioritize lower values.
		Subsystem->AddMappingContext(BaseMappingContext, BaseMappingPriority);
	}

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacterController::Jump);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacterController::StopJump);
		}

		if (InventoryAction)
			PlayerEnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &APlayerCharacterController::OpenCloseInventory);
		
		if (MovementAction)
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);

		if (LookAction)
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Look);

		if (DebugAction)
			PlayerEnhancedInputComponent->BindAction(DebugAction, ETriggerEvent::Started, this, &APlayerCharacterController::DebugKey);

		if (AttackAction)
			PlayerEnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacterController::Attack);

		if (Hotbar01Action)
			PlayerEnhancedInputComponent->BindAction(Hotbar01Action, ETriggerEvent::Triggered, this, &APlayerCharacterController::OnHotBar, 0);
		
		if (Hotbar02Action)
			PlayerEnhancedInputComponent->BindAction(Hotbar02Action, ETriggerEvent::Triggered, this, &APlayerCharacterController::OnHotBar, 1);

		if (Hotbar03Action)
			PlayerEnhancedInputComponent->BindAction(Hotbar03Action, ETriggerEvent::Triggered, this, &APlayerCharacterController::OnHotBar, 2);

		if (Hotbar04Action)
			PlayerEnhancedInputComponent->BindAction(Hotbar04Action, ETriggerEvent::Triggered, this, &APlayerCharacterController::OnHotBar,3);

		if (Hotbar05Action)
			PlayerEnhancedInputComponent->BindAction(Hotbar05Action, ETriggerEvent::Triggered, this, &APlayerCharacterController::OnHotBar, 4);

		if (Hotbar06Action)
			PlayerEnhancedInputComponent->BindAction(Hotbar06Action, ETriggerEvent::Triggered, this, &APlayerCharacterController::OnHotBar, 5);

		if (Hotbar07Action)
			PlayerEnhancedInputComponent->BindAction(Hotbar07Action, ETriggerEvent::Triggered, this, &APlayerCharacterController::OnHotBar, 6);

		if (Hotbar08Action)
			PlayerEnhancedInputComponent->BindAction(Hotbar08Action, ETriggerEvent::Triggered, this, &APlayerCharacterController::OnHotBar, 7);

		if (InteractAction)
			PlayerEnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacterController::Interact);
	}
}

void APlayerCharacterController::CloseInventory_Implementation()
{
	if (bIsInventoryShown == true)
	{
		FInputModeGameOnly InputMode;

		SetInputMode(InputMode);

		bIsInventoryShown = false;

		bShowMouseCursor = false;
	}
}

void APlayerCharacterController::OnHotBar(const FInputActionValue& Value, int32 Index)
{
	if (!bIsUsingItem)
	{
		HotBarIndex = Index;
		
		if (IsValid(PlayerRef->GetPlayerHotbar()))
		{
			PlayerRef->GetPlayerHotbar()->AddItem(PlayerRef->GetDebugStruct());
			
			if (EItemType Type; PlayerRef->GetPlayerHotbar()->CheckHotBar(Index, Type))
			{
				switch (Type)
				{
				case EItemType::EIT_Resource:
					break;
					
				case EItemType::EIT_Equippable:

					if (!IsValid(EquippedItemRef))
					{
						FItemsStruct LocalItem = PlayerRef->GetPlayerHotbar()->GetItemAtIndex(Index);

						if (auto&& Item = LocalItem.ItemAsset.LoadSynchronous(); IsValid(Item))
						{
							if (const TSubclassOf<AItemMaster> ItemClassRef = Item->ItemClassRef.LoadSynchronous(); IsValid(ItemClassRef))
								SpawnEquipableItem(ItemClassRef, Index);
						}
					}

					else
					{
						EquippedItemRef->Destroy();

						PlayerRef->SetState(EEquippableState::ES_Default);
					}
					
					break;
					
				case EItemType::EIT_Armour:
					break;
					
				case EItemType::EIT_Consumable:
					break;
					
				case EItemType::EIT_Buildable:
					break;

				default:
					break;
				}
			}
		}
	}
}

void APlayerCharacterController::Move(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0.F)
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), Value[1]);
		GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), Value[0]);
	}
}

void APlayerCharacterController::Look(const FInputActionValue& Value)
{
	AddPitchInput(Value[1] * -1);
	AddYawInput(Value[0]);
}

void APlayerCharacterController::OpenCloseInventory()
{
	if (bIsInventoryShown == true)
	{
		FInputModeGameOnly InputMode;

		SetInputMode(InputMode);

		bIsInventoryShown = false;

		bShowMouseCursor = false;
	}
	
	if (bIsInventoryShown == false)
	{
		if (IsValid(RootLayout))
		{
			RootLayout->PushGameInventoryLayout();

			FInputModeUIOnly UIOnly;

			SetInputMode(UIOnly);

			bIsInventoryShown = true;

			bShowMouseCursor = true;
		}
	}
}

void APlayerCharacterController::Attack()
{
	if (IsValid(EquippedItemRef))
	{
		IEquippableItemInterface::Execute_UseItem(EquippedItemRef, PlayerRef);
	}
}

void APlayerCharacterController::Interact()
{
	PlayerRef->OnClearViewport.Broadcast();
	
	PlayerRef->InteractWithObject();
}

void APlayerCharacterController::DebugKey()
{
	if (IsValid(PlayerRef))
		PlayerRef->InventoryDebug();
}

APlayerCharacterController* APlayerCharacterController::GetPlayerCharacterControllerRef_Implementation(){ return this; }

void APlayerCharacterController::Jump() { GetCharacter()->Jump(); }

void APlayerCharacterController::StopJump() { GetCharacter()->StopJumping(); }

void APlayerCharacterController::HideCraftItemToolTip_Implementation() { RootLayout->GameInventoryLayout->GameInventoryHideCraftItemToolTip(); }




