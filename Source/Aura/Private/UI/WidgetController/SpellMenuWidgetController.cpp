// Hey yo


#include "UI/WidgetController/SpellMenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	OnSpellPointsChangeDelegate.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraASC()->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 NewLevel)
	{
		if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
		{
			SelectedAbility.Status = StatusTag;
			bool bEnableSpendPoints = false;
			bool bEnableEquip = false;
			ShouldEnableButtons(StatusTag, CurrentSpellPoints, bEnableSpendPoints, bEnableEquip);

			FString Description;
			FString NextLevelDescription;
			GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag, Description, NextLevelDescription);

			OnSpellGlobeSelected.Broadcast(bEnableSpendPoints, bEnableEquip, Description, NextLevelDescription);
		}
		if (AbilityInfo)
		{
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.AbilityStatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});

	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda([this](int32 Points) 
	{
		OnSpellPointsChangeDelegate.Broadcast(Points);
		CurrentSpellPoints = Points;
		bool bEnableSpendPoints = false;
		bool bEnableEquip = false;
		ShouldEnableButtons(SelectedAbility.Status, CurrentSpellPoints, bEnableSpendPoints, bEnableEquip);

		FString Description;
		FString NextLevelDescription;
		GetAuraASC()->GetDescriptionsByAbilityTag(SelectedAbility.Ability, Description, NextLevelDescription);

		OnSpellGlobeSelected.Broadcast(bEnableSpendPoints, bEnableEquip, Description, NextLevelDescription);
	});
}

void USpellMenuWidgetController::ChangeButtonEnabledStatus(const FGameplayTag& AbilityTag)
{
	const int32 SpellPoints = GetAuraPS()->GetSpellPoints();
	const FGameplayAbilitySpec* AbilitySpec = GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);
	FGameplayTag StatusTag;

	if (!AbilityTag.IsValid() || AbilityTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_None) || !AbilitySpec)
	{
		StatusTag = FAuraGameplayTags::Get().Abilities_Status_Locked;
	}
	else
	{
		StatusTag = GetAuraASC()->GetStatusTagFromSpec(*AbilitySpec);
	}

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = StatusTag;

	bool bEnableSpendPoints = false;
	bool bEnableEquip = false;
	ShouldEnableButtons(StatusTag, SpellPoints, bEnableSpendPoints, bEnableEquip);

	FString Description;
	FString NextLevelDescription;
	GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag, Description, NextLevelDescription);

	OnSpellGlobeSelected.Broadcast(bEnableSpendPoints, bEnableEquip, Description, NextLevelDescription);
}

void USpellMenuWidgetController::SpendButtonPointButtonPressed()
{
	if (GetAuraASC())
	{
		GetAuraASC()->ServerSpendSpellPoint(SelectedAbility.Ability);
	}	
}

void USpellMenuWidgetController::GlobeDeselect()
{
	SelectedAbility.Ability = FAuraGameplayTags::Get().Abilities_None;
	SelectedAbility.Status = FAuraGameplayTags::Get().Abilities_Status_Locked;
	OnSpellGlobeSelected.Broadcast(false, false, FString(), FString());
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton)
{
	bShouldEnableEquipButton = false;
	bShouldEnableSpellPointsButton = false;

	if (AbilityStatus.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Eligible))
	{
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
	if (AbilityStatus.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Equipped) || AbilityStatus.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Unlocked))
	{
		bShouldEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
}
