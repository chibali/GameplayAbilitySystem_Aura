// Hey yo


#include "AbilitySystem/Abilities/AuraFireBlast.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetAbilityCost(Level));
	const float Cooldown = GetCooldown(Level);

	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>Fire Blast</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		//Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Description
		"<Default>Launches </><Level>%d </><Default>fire balls in all directions,"
		"each coming back and exploding upon return, causing: </><Damage>%d </>"
		"<Default>radial fire damage with a chance to burn</>"),
		Level,
		ManaCost,
		Cooldown,
		NumFireballs,
		ScaledDamage);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetAbilityCost(Level));
	const float Cooldown = GetCooldown(Level);
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>Next Level</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		//Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Description
		"<Default>Launches </><Level>%d </><Default>fire balls in all directions,"
		"each coming back and exploding upon return, causing: </><Damage>%d </>"
		"<Default>radial fire damage with a chance to burn</>"),
		Level,
		ManaCost,
		Cooldown,
		NumFireballs,
		ScaledDamage);
}
