// Hey yo


#include "AbilitySystem/Abilities/AuraFireBolt.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>Fire Bolt</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		//Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Description
		"<Default>Launches </><Level>%d </><Default>bolts of fire,"
		"exploding on impact and dealing: </><Damage>%d </>"
		"<Default>fire damage with a chance to burn</>"), 
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles), 
		ScaledDamage);
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetManaCost(Level));
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
		"<Default>Launches </><Level>%d </><Default>bolts of fire,"
		"exploding on impact and dealing: </><Damage>%d </>"
		"<Default>fire damage with a chance to burn</>"),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		ScaledDamage);
}