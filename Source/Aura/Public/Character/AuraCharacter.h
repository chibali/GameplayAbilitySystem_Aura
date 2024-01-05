// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//~ Begin Player Interface
	void AddToXP_Implementation(int InXP) override;
	//~ End Player Interface

	//~ Begin Combat Interface
	virtual int32 GetPlayerLevel() override;
	//~ End Combat Interface
private:
	void InitAbilityActorInfo() override;
};
