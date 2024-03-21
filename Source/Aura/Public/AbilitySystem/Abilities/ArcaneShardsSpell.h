// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "ArcaneShardsSpell.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UArcaneShardsSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
public:

	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Beam")
	int32 MaxNumArcaneShards = 5;
};
