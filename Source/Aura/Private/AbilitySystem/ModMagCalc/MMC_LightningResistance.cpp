// Hey yo

#include "AbilitySystem/ModMagCalc/MMC_LightningResistance.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_LightningResistance::UMMC_LightningResistance()
{
	ResilienceDef.AttributeToCapture = UAuraAttributeSet::GetResilienceAttribute();
	ResilienceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ResilienceDef.bSnapshot = false;

	LightningResistanceBonusDef.AttributeToCapture = UAuraAttributeSet::GetLightningResistanceBonusAttribute();
	LightningResistanceBonusDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	LightningResistanceBonusDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ResilienceDef);
	RelevantAttributesToCapture.Add(LightningResistanceBonusDef);
}

float UMMC_LightningResistance::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
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

	float LightningResistanceBonus = 0.f;
	GetCapturedAttributeMagnitude(LightningResistanceBonusDef, Spec, EvaluationParameters, LightningResistanceBonus);

	return ((1.5 + Resilience) * 0.5) + LightningResistanceBonus;
}