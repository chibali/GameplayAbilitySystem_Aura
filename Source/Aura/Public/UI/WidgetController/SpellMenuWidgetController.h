// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonStatusChangedSignature, bool, bIsEnabled);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintCallable)
	void ChangeButtonEnabledStatus(const FGameplayTag& AbilityTag);

	UPROPERTY(BlueprintAssignable, Category = "GAS|Level")
	FOnPlayerStatChangedSignature OnSpellPointsChangeDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Buttons")
	FOnButtonStatusChangedSignature OnSpendPointButtonEnabledDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Buttons")
	FOnButtonStatusChangedSignature OnEquipButtonEnabledDelegate;
};
