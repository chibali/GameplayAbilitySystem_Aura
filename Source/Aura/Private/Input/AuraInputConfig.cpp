// Hey yo


#include "Input/AuraInputConfig.h"
#include "InputAction.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
    for (const FAuraInputAction& InputAction : AbilityInputActions)
    {
        if (InputAction.InputAction && InputAction.InputTag.MatchesTagExact(InputTag))
        {
            return InputAction.InputAction;
        }
    }
    if (bLogNotFound == true)
    {
        UE_LOG(LogTemp, Error, TEXT("Can't find InputAction for InputTag [%s] on AuraInputAction [%s]"), *InputTag.ToString(), *GetNameSafe(this));
    }
    return nullptr;
}
