// Cat Cat Cat


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound)
{
	for (const FAuraInputAction AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.InputAction && AbilityInputAction.InputTag.MatchesTag(InputTag)) {
			return AbilityInputAction.InputAction;
		}
	}
	if (bLogNotFound) {
		UE_LOG(LogTemp, Error, TEXT("can't find ability input tag %s for config %s"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
