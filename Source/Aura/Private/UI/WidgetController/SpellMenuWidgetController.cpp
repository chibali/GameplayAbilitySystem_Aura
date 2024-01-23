// Hey yo


#include "UI/WidgetController/SpellMenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AuraGameplayTags.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	OnSpellPointsChangeDelegate.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraASC()->AbilityStatusChanged.AddLambda(
		[this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag)
	{
		if (AbilityInfo)
		{
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.AbilityStatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});
	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 Points) 
	{
		OnSpellPointsChangeDelegate.Broadcast(Points);
	});
}

void USpellMenuWidgetController::ChangeButtonEnabledStatus(const FGameplayTag& AbilityTag)
{
	if (GetAuraPS()->GetSpellPoints() > 0)
	{
		OnEquipButtonEnabledDelegate.Broadcast(false);
		OnSpendPointButtonEnabledDelegate.Broadcast(true);
	}

	if (AbilityTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_None))
	{
		OnEquipButtonEnabledDelegate.Broadcast(false);
		OnSpendPointButtonEnabledDelegate.Broadcast(false);
		return;
	}
	const FGameplayAbilitySpec* AbilitySpec = GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);
	if (AbilitySpec == nullptr)
	{
		OnEquipButtonEnabledDelegate.Broadcast(false);
		OnSpendPointButtonEnabledDelegate.Broadcast(false);
		return;
	}

	const FGameplayTag StatusTag = GetAuraASC()->GetStatusTagFromSpec(*AbilitySpec);
	if (StatusTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Locked))
	{
		OnEquipButtonEnabledDelegate.Broadcast(false);
		OnSpendPointButtonEnabledDelegate.Broadcast(false);
	}
	if (StatusTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Eligible))
	{
		OnEquipButtonEnabledDelegate.Broadcast(false);
		OnSpendPointButtonEnabledDelegate.Broadcast(true);
	}
	if (StatusTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Equipped) || StatusTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Unlocked))
	{
		OnEquipButtonEnabledDelegate.Broadcast(true);
		OnSpendPointButtonEnabledDelegate.Broadcast(true);
	}

	//if (AbilityInfo)
	//{
	//	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	//	if (Info.AbilityStatusTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Locked))
	//	{
	//		OnEquipButtonEnabledDelegate.Broadcast(false);
	//		OnSpendPointButtonEnabledDelegate.Broadcast(false);
	//	}
	//	if (Info.AbilityStatusTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Eligible))
	//	{
	//		OnEquipButtonEnabledDelegate.Broadcast(false);
	//		OnSpendPointButtonEnabledDelegate.Broadcast(true);
	//	}
	//	if (Info.AbilityStatusTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Equipped) || Info.AbilityStatusTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Unlocked))
	//	{
	//		OnEquipButtonEnabledDelegate.Broadcast(true);
	//		OnSpendPointButtonEnabledDelegate.Broadcast(true);
	//	}
	//}
}
