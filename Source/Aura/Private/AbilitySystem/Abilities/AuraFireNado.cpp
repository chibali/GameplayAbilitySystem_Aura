// Hey yo


#include "AbilitySystem/Abilities/AuraFireNado.h"
#include "Actor/AuraTornado.h"

void UAuraFireNado::SpawnFireNado(const FVector& TargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(TargetLocation);

	AAuraTornado* Tornado = GetWorld()->SpawnActorDeferred<AAuraTornado>(
		TornadoClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Tornado->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

	Tornado->FinishSpawning(SpawnTransform);
}

FString UAuraFireNado::GetDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetAbilityCost(Level));
	const float Cooldown = GetCooldown(Level);

	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>Fire Nado</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		//Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Description
		"<Default>Summons a growing fire tornado, "
		"that deals </><Damage>%d </><Default>damage every second and pulls enemies towards its center.</>"),
		Level,
		ManaCost,
		Cooldown,
		ScaledDamage);
}

FString UAuraFireNado::GetNextLevelDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetAbilityCost(Level));
	const float Cooldown = GetCooldown(Level);
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>Fire Nado</>\n\n"

		//Level
		"<Small>Level: </><Level>%d</>\n"
		//ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		//Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Description
		"<Default>Summons a growing fire tornado, "
		"that deals </><Damage>%d </><Default>damage every second and pulls enemies towards its center.</>"),
		Level,
		ManaCost,
		Cooldown,
		ScaledDamage);
}

