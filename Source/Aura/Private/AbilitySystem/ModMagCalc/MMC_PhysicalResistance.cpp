// Hey yo

#include "AbilitySystem/ModMagCalc/MMC_PhysicalResistance.h"
#include "AbilitySystem/AuraAttributeSet.h"

UMMC_PhysicalResistance::UMMC_PhysicalResistance()
{
	ResilienceDef.AttributeToCapture = UAuraAttributeSet::GetResilienceAttribute();
	ResilienceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ResilienceDef.bSnapshot = false;

	PhysicalResistanceBonusDef.AttributeToCapture = UAuraAttributeSet::GetPhysicalResistanceBonusAttribute();
	PhysicalResistanceBonusDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	PhysicalResistanceBonusDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ResilienceDef);
	RelevantAttributesToCapture.Add(PhysicalResistanceBonusDef);
}

float UMMC_PhysicalResistance::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
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

	float PhysicalResistanceBonus = 0.f;
	GetCapturedAttributeMagnitude(PhysicalResistanceBonusDef, Spec, EvaluationParameters, PhysicalResistanceBonus);

	return ((1.5 + Resilience) * 0.7) + PhysicalResistanceBonus;
}