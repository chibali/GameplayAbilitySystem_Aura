// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraFireNado.generated.h"

class AAuraTornado;

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

	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAuraTornado> TornadoClass;
};
