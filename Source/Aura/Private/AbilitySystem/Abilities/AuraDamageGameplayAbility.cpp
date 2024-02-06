// Hey yo


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass);

	const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, DamageType, ScaledDamage);

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
	
}

FDamageEffectParams UAuraDamageGameplayAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor) const
{
	FDamageEffectParams EffectParams;
	EffectParams.WorldContextObject = GetAvatarActorFromActorInfo();
	EffectParams.DamageGameplayEffectClass = DamageEffectClass;
	EffectParams.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	EffectParams.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	EffectParams.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	EffectParams.AbilityLevel = GetAbilityLevel();
	EffectParams.DamageType = DamageType;
	EffectParams.DebuffChance = DebuffChance.GetValueAtLevel(GetAbilityLevel());
	EffectParams.DebuffDamage = DebuffDamage.GetValueAtLevel(GetAbilityLevel());
	EffectParams.DebuffDuration = DebuffDuration;
	EffectParams.DebuffFrequency = DebuffFrequency;
	EffectParams.DeathImpulseMagnitude = DeathImpulseMagnitude;

	return EffectParams;
}

FTaggedMontage UAuraDamageGameplayAbility::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const
{
	if (TaggedMontages.Num() > 0)
	{
		const int32 Selection = FMath::RandRange(0, TaggedMontages.Num() - 1);
		return TaggedMontages[Selection];
	}

	return FTaggedMontage();
}


