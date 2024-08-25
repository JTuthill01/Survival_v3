#include "Items/Equippables/Tools/Hatchet/Stone/StoneHatchet.h"

AStoneHatchet::AStoneHatchet()
{
	SocketName = FName("HatchetSocket");

	AnimationState = EEquippableState::ES_Hatchet;
}
