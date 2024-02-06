// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

	void DetermineKnockback(const FGameplayEffectSpec& Spec) const;

	void DetermineDebuff(
		const FGameplayEffectSpec& Spec, 
		const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
		FAggregatorEvaluateParameters& EvaluateParams, 
		const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToCaptureDefs) const;
};
