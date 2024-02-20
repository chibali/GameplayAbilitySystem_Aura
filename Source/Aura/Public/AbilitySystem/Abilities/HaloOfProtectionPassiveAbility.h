// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraPassiveAbility.h"
#include "HaloOfProtectionPassiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHaloOfProtectionPassiveAbility : public UAuraPassiveAbility
{
	GENERATED_BODY()

public:

	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat ElementalResistanceBonus;
};
