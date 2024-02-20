// Hey yo


#include "AbilitySystem/ModMagCalc/MMC_ArcaneResistance.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_ArcaneResistance::UMMC_ArcaneResistance()
{
	ResilienceDef.AttributeToCapture = UAuraAttributeSet::GetResilienceAttribute();
	ResilienceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ResilienceDef.bSnapshot = false;

	ArcaneResistanceBonusDef.AttributeToCapture = UAuraAttributeSet::GetArcaneResistanceBonusAttribute();
	ArcaneResistanceBonusDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ArcaneResistanceBonusDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ResilienceDef);
	RelevantAttributesToCapture.Add(ArcaneResistanceBonusDef);
}

float UMMC_ArcaneResistance::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
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

	float ArcaneResistanceBonus = 0.f;
	GetCapturedAttributeMagnitude(ArcaneResistanceBonusDef, Spec, EvaluationParameters, ArcaneResistanceBonus);

	return ((1.5 + Resilience) * 0.5) + ArcaneResistanceBonus;
}
