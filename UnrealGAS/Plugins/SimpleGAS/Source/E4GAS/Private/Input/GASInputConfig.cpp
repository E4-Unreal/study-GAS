#include "Input/GASInputConfig.h"
#include "GameplayTagContainer.h"
#include "EnhancedInput/Public/InputAction.h"

const UInputAction* UGASInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FTaggedInputAction& TaggedInputAction : NativeInputActions)
	{
		if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
		{
			return TaggedInputAction.InputAction;
		}
	}

	return nullptr;
}

const UInputAction* UGASInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FTaggedInputAction& TaggedInputAction : AbilityInputActions)
	{
		if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
		{
			return TaggedInputAction.InputAction;
		}
	}

	return nullptr;
}

EGASAbilityID UAbilityInputConfig::FindAbilityIDForTag(const FGameplayTag& InputTag) const
{
	for (const FTaggedAbilityID& TaggedAbilityID : TaggedAbilityIDs)
	{
		if (TaggedAbilityID.AbilityID != EGASAbilityID::None && TaggedAbilityID.InputTag == InputTag)
		{
			return TaggedAbilityID.AbilityID;
		}
	}

	return EGASAbilityID::None;
}
