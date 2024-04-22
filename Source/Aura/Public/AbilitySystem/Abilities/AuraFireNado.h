// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraFireNado.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFireNado : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SpawnFireNado(const FVector& TargetLocation);
};
