#include "Items/EquippableMaster/EquippableMaster.h"

AEquippableMaster::AEquippableMaster() : SocketName(FName()), AnimationState(EEquippableState::ES_Default)
{
}

void AEquippableMaster::GetEquippableInfo_Implementation(FName& OutSocketName, EEquippableState& OutState)
{
	OutSocketName = SocketName;

	OutState = AnimationState;
}

void AEquippableMaster::UseItem_Implementation(AActor* CharacterRef)
{
}

void AEquippableMaster::NotifyInterface_Implementation()
{
}
