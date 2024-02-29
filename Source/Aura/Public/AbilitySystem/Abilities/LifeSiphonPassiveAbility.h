// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraPassiveAbility.h"
#include "LifeSiphonPassiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ULifeSiphonPassiveAbility : public UAuraPassiveAbility
{
	GENERATED_BODY()

public:

	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

	UFUNCTION(BlueprintPure)
	float GetLifeStealAtLevel() const;

private:

	UPROPERTY(EditAnywhere)
	FScalableFloat LifeSteal;
};
