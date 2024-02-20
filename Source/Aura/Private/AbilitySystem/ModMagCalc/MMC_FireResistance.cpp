// Hey yo


#include "AbilitySystem/ModMagCalc/MMC_FireResistance.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_FireResistance::UMMC_FireResistance()
{
	ResilienceDef.AttributeToCapture = UAuraAttributeSet::GetResilienceAttribute();
	ResilienceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ResilienceDef.bSnapshot = false;

	FireResistanceBonusDef.AttributeToCapture = UAuraAttributeSet::GetFireResistanceBonusAttribute();
	FireResistanceBonusDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	FireResistanceBonusDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ResilienceDef);
	RelevantAttributesToCapture.Add(FireResistanceBonusDef);
}

float UMMC_FireResistance::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Resilience = 0.f;
	GetCapturedAttributeMagnitude(ResilienceDef, Spec, EvaluationParameters, Resilience);

	Resilience = FMath::Max<float>(Resilience, 0.f);

	float FireResistanceBonus = 0.f;
	GetCapturedAttributeMagnitude(FireResistanceBonusDef, Spec, EvaluationParameters, FireResistanceBonus);

	return ((1.5 + Resilience) * 0.5) + FireResistanceBonus;
}
