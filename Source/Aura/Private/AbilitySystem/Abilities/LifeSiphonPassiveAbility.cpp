// Hey yo


#include "AbilitySystem/Abilities/LifeSiphonPassiveAbility.h"
#include "AbilitySystemBlueprintLibrary.h"

FString ULifeSiphonPassiveAbility::GetDescription(int32 Level)
{
	const float AbilityCost = FMath::Abs(GetAbilityCost(Level)) * 100;

	const int32 ScaledLifeSteal = LifeSteal.GetValueAtLevel(Level) * 100;;
	return FString::Printf(TEXT(
		//Title
		"<Title>Life Siphon</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		"<Small>Ability Cost:</><Cooldown> Reserves </><LifeCost>%.1f percent</><Cooldown> of MaxHealth</>\n\n"

		//Description
		"<Default>Steals life essence from enemies. When equipped, restores </><Percent>%d percent"
		"%"
		"</><Default> of the damage dealt.</>"),
		Level,
		AbilityCost,
		ScaledLifeSteal);
}

FString ULifeSiphonPassiveAbility::GetNextLevelDescription(int32 Level)
{
	const float AbilityCost = FMath::Abs(GetAbilityCost(Level)) * 100;

	const int32 ScaledLifeSteal = LifeSteal.GetValueAtLevel(Level) * 100;;
	return FString::Printf(TEXT(
		//Title
		"<Title>Next Level</>\n\n"
		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		"<Small>Ability Cost:</><Cooldown> Reserves </><LifeCost>%.1f percent</><Cooldown> of MaxHealth</>\n\n"

		//Description
		"<Default>Steals life essence from enemies. When equipped, restores </><Percent>%d percent"
		"%"
		"</><Default> of the damage dealt.</>"),
		Level,
		AbilityCost,
		ScaledLifeSteal);
}

float ULifeSiphonPassiveAbility::GetLifeStealAtLevel() const
{
	return LifeSteal.GetValueAtLevel(GetAbilityLevel());
}
