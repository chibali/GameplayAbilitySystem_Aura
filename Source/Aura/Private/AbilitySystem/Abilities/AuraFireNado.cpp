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

	// TO DO: Assign Radial Damage
	// 
	// Tornado->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

	Tornado->FinishSpawning(SpawnTransform);
}

