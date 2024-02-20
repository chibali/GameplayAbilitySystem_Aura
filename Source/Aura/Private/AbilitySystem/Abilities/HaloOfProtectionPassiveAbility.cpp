// Hey yo


#include "AbilitySystem/Abilities/HaloOfProtectionPassiveAbility.h"

FString UHaloOfProtectionPassiveAbility::GetDescription(int32 Level)
{
	/*const float ManaCost = FMath::Abs(GetManaCost(Level));*/

	const int32 ScaledElementalResistanceBonus = ElementalResistanceBonus.GetValueAtLevel(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>Halo of Protection</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		//"<Small>ManaCost: /*</><ManaCost>%.1f</>*/\n"

		//Description
		"<Default>Grants protection to those who seek it. When equipped, grants a flat </><Percent>%d"
		"%"
		"</><Default> bonus to every resistance.</>"),
		Level,
		//ManaCost,
		ScaledElementalResistanceBonus);
}

FString UHaloOfProtectionPassiveAbility::GetNextLevelDescription(int32 Level)
{
	/*const float ManaCost = FMath::Abs(GetManaCost(Level));*/

	const int32 ScaledElementalResistanceBonus = ElementalResistanceBonus.GetValueAtLevel(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>Next Level</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		//"<Small>ManaCost: /*</><ManaCost>%.1f</>*/\n"

		//Description
		"<Default>Grants protection to those who seek it. When equipped, grants a flat </><Percent>%d"
		"%"
		"</><Default> bonus to every resistance.</>"),
		Level,
		//ManaCost,
		ScaledElementalResistanceBonus);
}
