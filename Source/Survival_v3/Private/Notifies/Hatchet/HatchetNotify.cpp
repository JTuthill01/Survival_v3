#include "Notifies/Hatchet/HatchetNotify.h"
#include "Character/Player/PlayerCharacter.h"
#include "Items/Equippables/Tools/Hatchet/Master/HatchetMaster.h"

void UHatchetNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp->GetOwner()))
	{
		if (auto&& Player = Cast<APlayerCharacter>(MeshComp->GetOwner()); IsValid(Player))
		{
			if (IsValid(Player->GetEquippedItem()))
			{
				IEquippableItemInterface::Execute_NotifyInterface(Player->GetEquippedItem());
			}
		}
	}
}
