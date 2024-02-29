// Hey yo


#include "AbilitySystem/Abilities/HaloOfProtectionPassiveAbility.h"

FString UHaloOfProtectionPassiveAbility::GetDescription(int32 Level)
{
	const float AbilityCost = FMath::Abs(GetAbilityCost(Level)) * 100;

	const int32 ScaledElementalResistanceBonus = ElementalResistanceBonus.GetValueAtLevel(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>Halo of Protection</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		"<Small>ManaCost:</><Cooldown> Reserves </><ManaCost>%.1f percent</><Cooldown> of MaxMana</>\n\n"

		//Description
		"<Default>Grants protection to those who seek it. When equipped, grants a flat </><Percent>%d percent"
		"%"
		"</><Default> bonus to every resistance.</>"),
		Level,
		AbilityCost,
		ScaledElementalResistanceBonus);
}

FString UHaloOfProtectionPassiveAbility::GetNextLevelDescription(int32 Level)
{
	const float AbilityCost = FMath::Abs(GetAbilityCost(Level)) * 100;

	const int32 ScaledElementalResistanceBonus = ElementalResistanceBonus.GetValueAtLevel(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>Next Level</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		"<Small>ManaCost:</><Cooldown> Reserves </><ManaCost>%.1f percent</><Cooldown> of MaxMana</>\n\n"

		//Description
		"<Default>Grants protection to those who seek it. When equipped, grants a flat </><Percent>%d percent"
		"%"
		"</><Default> bonus to every resistance.</>"),
		Level,
		AbilityCost,
		ScaledElementalResistanceBonus);
}
