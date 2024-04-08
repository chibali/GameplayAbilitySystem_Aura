// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
class UAbilityInfo;
class UAuraAbilitySystemComponent;
struct FOnAttributeChangeData;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelChangedSignature, int32, NewLevel, bool, bLevelUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPassiveActivatedSignature, float, OriginalMaxResource, bool, bIsActive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelUpPassiveActive, float, OriginalMaxResource, float, CurrentMaxResource);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	void BroadcastInitialValues() override;
	void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Level")
	FOnLevelChangedSignature OnPlayerLevelChangeDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|XP")
	FOnAttributeChangedSignature OnXPPercentChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnPassiveActivatedSignature OnHaloOfProtectionActivatedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnPassiveActivatedSignature OnLifeSiphonActivatedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnLevelUpPassiveActive OnLevelUpHaloOfProtectionActive;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnLevelUpPassiveActive OnLevelUpLifeSiphonActive;

	UFUNCTION(BlueprintCallable)
	void OnXPChanged(int32 XP);

	UFUNCTION(BlueprintCallable)
	void OnPassiveAbilityActivated(const FGameplayTag& PassiveTag, bool bIsActive);

	UFUNCTION(BlueprintCallable)
	void OnHaloOfProtectionActiveLevelUp(float NewMaxMana);

	UFUNCTION(BlueprintCallable)
	void OnLifeSiphonActiveLevelUp(float NewMaxHealth);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

	void OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& AbilityStatus, const FGameplayTag& NewSlot, const FGameplayTag& PreviousSlot);

private:
	float GetUnreservedMaxMana();
	float GetUnreservedMaxHealth();
};

template<typename T>
inline T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
