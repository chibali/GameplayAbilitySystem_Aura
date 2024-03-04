// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraPassiveAbility.h"
#include "ManaSiphonPassiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UManaSiphonPassiveAbility : public UAuraPassiveAbility
{
	GENERATED_BODY()

public:

	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

private:
	UPROPERTY(EditAnywhere)
	FScalableFloat ManaSiphonRegen;

	UPROPERTY(EditAnywhere)
	FScalableFloat ManaSiphonFrequency;
};
