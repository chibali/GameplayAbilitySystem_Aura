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

FDamageEffectParams UAuraDamageGameplayAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor, 
	FVector InRadialDamageOrigin, bool bOverrideKnockbackDirection, FVector InKnockbackDirectionOverride, bool bOverrideDeathImpulse, 
	FVector InDeathImpulseDirectionOverride, bool bOverridePitch, float PitchOverride) const
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
	EffectParams.KnockbackChance = KnockbackChance;
	EffectParams.KnockbackMagnitude = KnockbackMagnitude;

	if (IsValid(TargetActor))
	{
		FRotator Rotation = (TargetActor->GetActorLocation() - GetAvatarActorFromActorInfo()->GetActorLocation()).Rotation();
		if (bOverridePitch)
		{
			Rotation.Pitch = PitchOverride;
		}
		const FVector ToTarget = Rotation.Vector();

		if (!bOverrideKnockbackDirection)
		{
			EffectParams.Knockback = ToTarget * KnockbackMagnitude;
		}
		if (!bOverrideDeathImpulse)
		{
			EffectParams.DeathImpulse = ToTarget * DeathImpulseMagnitude;
		}
	}
	
	
	if (bOverrideKnockbackDirection)
	{
		InKnockbackDirectionOverride.Normalize();
		EffectParams.Knockback = InKnockbackDirectionOverride * KnockbackMagnitude;
		if (bOverridePitch)
		{
			FRotator KnockbackRotation = InKnockbackDirectionOverride.Rotation();
			KnockbackRotation.Pitch = PitchOverride;
			EffectParams.Knockback = KnockbackRotation.Vector() * KnockbackMagnitude;
		}
	}

	if (bOverrideDeathImpulse)
	{
		InDeathImpulseDirectionOverride.Normalize();
		EffectParams.DeathImpulse = InDeathImpulseDirectionOverride * DeathImpulseMagnitude;
		if (bOverridePitch)
		{
			FRotator DeathImpulseRotation = InDeathImpulseDirectionOverride.Rotation();
			DeathImpulseRotation.Pitch = PitchOverride;
			EffectParams.DeathImpulse = DeathImpulseRotation.Vector() * DeathImpulseMagnitude;
		}
	}

	if (bIsRadialDamage)
	{
		EffectParams.bIsRadialDamage = bIsRadialDamage;
		EffectParams.RadialDamageOrigin = InRadialDamageOrigin;
		EffectParams.RadialDamageInnerRadius = RadialDamageInnerRadius;
		EffectParams.RadialDamageOuterRadius = RadialDamageOuterRadius;
	}
	return EffectParams;
}

float UAuraDamageGameplayAbility::GetDamageAtLevel() const
{
	return Damage.GetValueAtLevel(GetAbilityLevel());
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


