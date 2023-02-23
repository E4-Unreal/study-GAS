// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Abilities/CharacterGameplayAbility.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"

UCharacterGameplayAbility::UCharacterGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	// Todo Native Tag로 교체?
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(("State.Dead")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(("State.Debuff.Stun")));
}

void UCharacterGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if(ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
