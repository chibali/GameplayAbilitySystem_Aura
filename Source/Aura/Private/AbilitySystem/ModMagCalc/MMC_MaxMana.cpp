// Hey yo


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"
#include "Aura/AuraLogChannels.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	HaloOfProtectionCostDef.AttributeToCapture = UAuraAttributeSet::GetHaloOfProtectionCostAttribute();
	HaloOfProtectionCostDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	HaloOfProtectionCostDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
	RelevantAttributesToCapture.Add(HaloOfProtectionCostDef);

}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 0.f);

	float HaloOfProtectionCost = 0.f;
	GetCapturedAttributeMagnitude(HaloOfProtectionCostDef, Spec, EvaluationParameters, HaloOfProtectionCost);
	HaloOfProtectionCost = FMath::Max<float>(HaloOfProtectionCost, 0.f);

	
	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetEffectCauser()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}
	return (60.f + 2 * Intelligence + 5 * PlayerLevel) * (1 - HaloOfProtectionCost);
}
