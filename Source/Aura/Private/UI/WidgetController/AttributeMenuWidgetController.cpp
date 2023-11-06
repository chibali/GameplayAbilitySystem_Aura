// Hey yo


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	if (AttributeInformation == nullptr) return;
	
	for (auto Pair : AuraAttributeSet->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeInformation->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AuraAttributeSet);
		AttributeInfoDelegate.Broadcast(Info);
	}

}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}
