// Hey yo


#include "AbilitySystem/Abilities/AuraLightningBeamSpell.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"

FString UAuraLightningBeamSpell::GetDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetAbilityCost(Level));
	const float Cooldown = GetCooldown(Level);

	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);

	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>Lightning Beam</>\n\n"

			//Level
			"<Small>Level: </><Level>%d</>\n"
			//ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			//Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Launches </><Level> </><Default>a powerful lightning beam, "
			"dealing </><Damage>%d </>"
			"<Default>lightning damage per application, with a chance to stun the target when the ability ends.</>"),
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else if (Level == 2)
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>Lightning Beam</>\n\n"

			//Level
			"<Small>Level: </><Level>%d</>\n"
			//ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			//Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Launches a powerful lightning beam, that spreads </><Time>to the closest enemy, </>"
			"<Default>dealing </><Damage>%d </>"
			"<Default>lightning damage per application, with a chance to stun the target when the ability ends.</>"),
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else 
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>Lightning Beam</>\n\n"

			//Level
			"<Small>Level: </><Level>%d</>\n"
			//ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			//Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Launches a powerful lightning beam, that spreads to the </><Level>%d</><Time> closest enemies, </>"
			"<Default>dealing </><Damage>%d </>"
			"<Default>lightning damage per application, with a chance to stun the target when the ability ends.</>"),
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level - 1, MaxNumShockTargets),
			ScaledDamage);
	}
	
}

FString UAuraLightningBeamSpell::GetNextLevelDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetAbilityCost(Level));
	const float Cooldown = GetCooldown(Level);
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);

	if (Level == 2)
	{
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
			"<Default>Launches a powerful lightning beam, that spreads </><Time>to the closest enemy, </>"
			"<Default>dealing </><Damage>%d </>"
			"<Default>lightning damage per application, with a chance to stun the target when the ability ends.</>"),
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
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
			"<Default>Launches a powerful lightning beam, that spreads to the </><Level>%d</><Time> closest enemies, </>"
			"<Default>dealing </><Damage>%d </>"
			"<Default>lightning damage per application, with a chance to stun the target when the ability ends.</>"),
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level - 1, MaxNumShockTargets),
			ScaledDamage);
	}

}

void UAuraLightningBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if (HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UAuraLightningBeamSpell::StoreOwnerVariables()
{
	if (CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
}

void UAuraLightningBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerCharacter);
	if (OwnerCharacter->Implements<UCombatInterface>())
	{
		if (USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			const FVector SocketLocation = Weapon->GetSocketLocation(FName("TipSocket"));
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(OwnerCharacter);
			FHitResult HitResult;
			UKismetSystemLibrary::SphereTraceSingle(
				OwnerCharacter,
				SocketLocation,
				BeamTargetLocation,
				10.f,
				TraceTypeQuery1,
				false,
				ActorsToIgnore,
				EDrawDebugTrace::None,
				HitResult,
				true
			);
			if (HitResult.bBlockingHit /*&& UAuraAbilitySystemLibrary::IsNotAlly(GetAvatarActorFromActorInfo(), HitResult.GetActor())*/)
			{
				MouseHitLocation = HitResult.ImpactPoint;
				MouseHitActor = HitResult.GetActor();
			}
		}
	}
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(MouseHitActor))
	{
		if (!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraLightningBeamSpell::PrimaryTargetDied))
		{
			CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraLightningBeamSpell::PrimaryTargetDied);
		}
	}
}

void UAuraLightningBeamSpell::StoreAdditionalTarget(TArray<AActor*>& OutAdditionalTargets)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	ActorsToIgnore.Add(MouseHitActor);

	TArray<AActor*> OverlappingActors;
	UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(
		GetAvatarActorFromActorInfo(),
		OverlappingActors,
		ActorsToIgnore,
		850.f,
		MouseHitActor->GetActorLocation());

	int32 NumAdditionalTargets = FMath::Min(GetAbilityLevel() - 1, MaxNumShockTargets);

	UAuraAbilitySystemLibrary::GetClosestTargets(NumAdditionalTargets, OverlappingActors, OutAdditionalTargets, MouseHitActor->GetActorLocation());

	for (AActor* Target : OutAdditionalTargets)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Target))
		{
			if (!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraLightningBeamSpell::AdditionalTargetDied))
			{
				CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraLightningBeamSpell::AdditionalTargetDied);
			}
		}
	}
}
