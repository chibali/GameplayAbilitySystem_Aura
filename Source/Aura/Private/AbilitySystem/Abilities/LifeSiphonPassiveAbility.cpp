// Hey yo


#include "AbilitySystem/Abilities/LifeSiphonPassiveAbility.h"
#include "AbilitySystemBlueprintLibrary.h"

float ULifeSiphonPassiveAbility::GetLifeStealAtLevel() const
{
	return LifeSteal.GetValueAtLevel(GetAbilityLevel());
}
