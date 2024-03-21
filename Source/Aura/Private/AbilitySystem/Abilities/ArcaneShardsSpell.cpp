// Hey yo


#include "AbilitySystem/Abilities/ArcaneShardsSpell.h"

FString UArcaneShardsSpell::GetDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetAbilityCost(Level));
	const float Cooldown = GetCooldown(Level);

	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);

	return FString::Printf(TEXT(
			//Title
			"<Title>Arcane Shards</>\n\n"

			//Level
			"<Small>Level: </><Level>%d</>\n"
			//ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			//Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Summons </><Level>%d </><Default> shards, "
			"dealing </><Damage>%d </>"
			"<Default>arcane damage to all enemies within range. Applies knockback to all targets hit.</>"),
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumArcaneShards),
			ScaledDamage);
}

FString UArcaneShardsSpell::GetNextLevelDescription(int32 Level)
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
		"<Default>Summons </><Level>%d </><Default> shards, "
		"dealing </><Damage>%d </>"
		"<Default>arcane damage to all enemies within range. Applies knockback to all targets hit.</>"),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxNumArcaneShards),
		ScaledDamage);
}
