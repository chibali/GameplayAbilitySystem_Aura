// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class ULevelUpInfo;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelChanged, int32 /*StatValue*/, bool /*bLevelUp*/);
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnLevelChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;
	FOnPlayerStatChanged OnSpellPointsChangedDelegate;

	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	void SetLevel(int32 InLevel);
	void AddToLevel(int32 LevelToAdd);

	FORCEINLINE int32 GetXP() const { return XP; }
	void SetXP(int32 InXP);
	void AddToXP(int32 XPToAdd);

	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
	void SetAttributePoints(int32 InAttributePoints);
	void AddToAttributePoints(int32 AttributePointsToAdd);

	FORCEINLINE int32 GetSpellPoints() const { return SpellPoints; }
	void SetSpellPoints(int32 InSpellPoints);
	void AddToSpellPoints(int32 SpellPointsToAdd);

	UPROPERTY(EditDefaultsOnly, Category = "Level Up Information")
	TObjectPtr<ULevelUpInfo> LevelUpInformation;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level, Category = "Level")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP, Category = "Level");
	int32 XP = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_AttributePoints, Category = "Level")
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SpellPoints, Category = "Level")
	int32 SpellPoints = 0;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);
};
