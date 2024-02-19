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
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat DamageReduction;
};
