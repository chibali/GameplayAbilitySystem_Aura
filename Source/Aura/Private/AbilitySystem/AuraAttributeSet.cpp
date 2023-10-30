// Hey yo


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(25.f);
	InitMaxHealth(100.f);
	InitMana(35.f);
	InitMaxMana(100.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Properties) const
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Source == Causer of the effect, Target = target of the effect (owner of this attribute set)
		Properties.EffectContextHandle = Data.EffectSpec.GetContext();
		Properties.SourceAbilitySystemComponent = Properties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

		if (IsValid(Properties.SourceAbilitySystemComponent) && Properties.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() && Properties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
		{
			Properties.SourceAvatarActor = Properties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
			Properties.SourceController = Properties.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
			if (Properties.SourceController == nullptr && Properties.SourceAvatarActor != nullptr)
			{
				if (const APawn* Pawn = Cast<APawn>(Properties.SourceAvatarActor))
				{
					Properties.SourceController = Pawn->GetController();

				}
			}
			if (Properties.SourceController)
			{
				Properties.SourceCharacter = Cast<ACharacter>(Properties.SourceController->GetPawn());
			}
		}
		if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
		{
			Properties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
			Properties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
			Properties.TargetCharacter = Cast<ACharacter>(Properties.TargetAvatarActor);
		}
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Properties;
	SetEffectProperties(Data, Properties);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetHealth(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}


