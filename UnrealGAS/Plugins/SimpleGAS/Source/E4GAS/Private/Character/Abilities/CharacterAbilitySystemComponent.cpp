// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/CharacterAbilitySystemComponent.h"

#include "Input/GASInputComponent.h"

void UCharacterAbilitySystemComponent::BindAbilityActivationToEnhancedInputComponent(UInputComponent* InputComponent,
	FGameplayAbilityInputBinds BindInfo)
{
}

void UCharacterAbilitySystemComponent::ReceiveDamage(UCharacterAbilitySystemComponent* SourceASC,
                                                     float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
	
}
