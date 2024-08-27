// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri


#include "Interaction/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.

int32 ICombatInterface::GetPlayerLevel()
{
	return 0;
}

FVector ICombatInterface::GetCombatSocketLocation()
{
	return FVector();
}

FVector ICombatInterface::GetRootSocketLocation()
{
	return FVector();
}