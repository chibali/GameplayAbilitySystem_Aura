// Hey yo


#include "AbilitySystem/Abilities/ManaSiphonPassiveAbility.h"

FString UManaSiphonPassiveAbility::GetDescription(int32 Level)
{
	const int32 AbilityFrequency = ManaSiphonFrequency.GetValueAtLevel(Level);

	const int32 ScaledManaRegen = ManaSiphonRegen.GetValueAtLevel(Level) * 100;;
	return FString::Printf(TEXT(
		//Title
		"<Title>Mana Siphon</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n\n"
		////ManaCost
		/*"<Small>Ability Cost:</><Cooldown> Reserves </><LifeCost>%.1f percent</><Cooldown> of MaxHealth</>\n\n"*/

		//Description
		"<Default>Regenerates the ether of magic. Every </><Time>%d seconds</><Default>, restores </><Percent>%d percent"
		"%"
		"</><Default> of missing mana on hit.</>"),
		Level,
		AbilityFrequency,
		ScaledManaRegen);
}

FString UManaSiphonPassiveAbility::GetNextLevelDescription(int32 Level)
{
	const int32 AbilityFrequency = ManaSiphonFrequency.GetValueAtLevel(Level);

	const int32 ScaledManaRegen = ManaSiphonRegen.GetValueAtLevel(Level) * 100;;
	return FString::Printf(TEXT(
		//Title
		"<Title>Next Level</>\n\n"
		//Level
		"<Small>Level: </><Level>%d</>\n\n"
		////ManaCost
		/*"<Small>Ability Cost:</><Cooldown> Reserves </><LifeCost>%.1f percent</><Cooldown> of MaxHealth</>\n\n"*/

		//Description
		"<Default>Regenerates the ether of magic. Every </><Time>%d seconds</><Default>, restores </><Percent>%d percent"
		"%"
		"</><Default> of missing mana on hit.</>"),
		Level,
		AbilityFrequency,
		ScaledManaRegen);
}
