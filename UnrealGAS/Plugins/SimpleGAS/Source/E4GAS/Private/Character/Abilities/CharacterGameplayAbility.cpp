// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Abilities/CharacterGameplayAbility.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "GASGameplayTags.h"

UCharacterGameplayAbility::UCharacterGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	ActivationBlockedTags.AddTag(FGASGameplayTags::Get().State_Dead);
	ActivationBlockedTags.AddTag(FGASGameplayTags::Get().State_Debuff_Stun);

	// Debug for Native Gameplay Tag is applied
	// UE_LOG(LogTemp, Error, TEXT("%s"), *GetName())
	// UE_LOG(LogTemp, Error, TEXT("%d"), ActivationBlockedTags.Num())
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
