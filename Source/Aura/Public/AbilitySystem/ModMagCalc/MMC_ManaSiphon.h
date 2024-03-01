// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_ManaSiphon.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_ManaSiphon : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_ManaSiphon();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition MaxManaDef;
	FGameplayEffectAttributeCaptureDefinition ManaDef;
};
