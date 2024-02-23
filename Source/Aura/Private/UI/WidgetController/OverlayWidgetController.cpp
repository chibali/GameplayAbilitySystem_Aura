// Hey yo


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Data/AbilityInfo.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetAuraAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetAuraAS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetAuraAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetAuraAS()->GetMaxMana());
	OnXPPercentChangedDelegate.Broadcast(0.f);
	OnHaloOfProtectionActivatedDelegate.Broadcast(GetAuraAS()->GetMaxMana(), false);
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetAuraAS()->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {OnHealthChanged.Broadcast(Data.NewValue); });
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetAuraAS()->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {OnMaxHealthChanged.Broadcast(Data.NewValue); });
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetAuraAS()->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {OnManaChanged.Broadcast(Data.NewValue); });
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetAuraAS()->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {OnMaxManaChanged.Broadcast(Data.NewValue); });
	GetAuraASC()->ActivatePassiveAbility.AddUObject(this, &UOverlayWidgetController::OnHaloOfProtectionActivated);

	GetAuraPS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	
	GetAuraPS()->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel) {
			OnPlayerLevelChangeDelegate.Broadcast(NewLevel);
		}
	);


	if (GetAuraASC())
	{
		if (GetAuraASC()->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else
		{
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}
		

		GetAuraASC()->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
		
		GetAuraASC()->AbilityEquipped.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);
	}
	
}

void UOverlayWidgetController::OnXPChanged(int32 XP) 
{
	ULevelUpInfo* LevelUpInfo = GetAuraPS()->LevelUpInformation;
	checkf(LevelUpInfo, TEXT("Unable to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));

	const int32 CurrentLevel = LevelUpInfo->FindLevelForXP(XP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (CurrentLevel <= MaxLevel && CurrentLevel > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[CurrentLevel].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[CurrentLevel - 1].LevelUpRequirement;
		const int32 DeltaLevelUpRequirement = LevelUpRequirement - PreviousLevelUpRequirement;

		const int32 XPForThisLevel = XP - PreviousLevelUpRequirement;

		const float XPPercent = (static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelUpRequirement));

		OnXPPercentChangedDelegate.Broadcast(XPPercent);
	}
}

void UOverlayWidgetController::OnHaloOfProtectionActivated(const FGameplayTag& PassiveTag, bool bIsActive)
{
	if (PassiveTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Passive_HaloOfProtection))
	{
		float OriginalMaxMana = GetAuraAS()->GetMaxMana();
		float HaloOfProtectionCostCoefficient = (1 - GetAuraAS()->GetHaloOfProtectionCost());
		OriginalMaxMana = OriginalMaxMana / HaloOfProtectionCostCoefficient;
		OnHaloOfProtectionActivatedDelegate.Broadcast(OriginalMaxMana, bIsActive);
	}
}

void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& AbilityStatus, const FGameplayTag& NewSlot, const FGameplayTag& PreviousSlot)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	FAuraAbilityInfo LastSlotInfo;
	LastSlotInfo.AbilityStatusTag = GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PreviousSlot;
	LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;
	// Broadcast empty info if PreviousSlot is a valid slot. Only if equipping on already equipped spell.
	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FAuraAbilityInfo NewSlotInfo = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	NewSlotInfo.AbilityStatusTag = AbilityStatus;
	NewSlotInfo.InputTag = NewSlot;
	AbilityInfoDelegate.Broadcast(NewSlotInfo);
}
