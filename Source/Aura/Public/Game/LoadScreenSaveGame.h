// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

UENUM(BlueprintType)
enum ESaveSlotStatus
{
	Vacant,
	EnterName,
	Taken
};

/**
 * 
 */
UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY()
	FString SlotName = FString();

	UPROPERTY()
	int32 SlotIndex = 0;

	UPROPERTY()
	FString PlayerName = FString("Default Name");

	UPROPERTY()
	FString MapName = FString("Default Map Name");

	UPROPERTY()
	FName PlayerStartTag;

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;

	/* Player */

	UPROPERTY()
	int32 PlayerLevel = 0;

	UPROPERTY()
	int32 PlayerXP = 0;

	UPROPERTY()
	int32 Spellpoints = 0;

	UPROPERTY()
	int32 AttributePoints = 0;


	UPROPERTY()
	float Strength = 0;

	UPROPERTY()
	float Intelligence = 0;

	UPROPERTY()
	float Dexterity = 0;

	UPROPERTY()
	float Resilience = 0;

	UPROPERTY()
	float Vigor = 0;

	/*UPROPERTY()
	float FireResistanceBonus = 0;

	UPROPERTY()
	float LightningResistanceBonus = 0;

	UPROPERTY()
	float ArcaneResistanceBonus = 0;

	UPROPERTY()
	float PhysicalResistanceBonus = 0;

	UPROPERTY()
	float HaloOfProtectionCost = 0;

	UPROPERTY()
	float LifeSteal = 0;

	UPROPERTY()
	float LifeSiphonCost = 0;

	UPROPERTY()
	float ManaSiphonRegen = 0;*/


};
