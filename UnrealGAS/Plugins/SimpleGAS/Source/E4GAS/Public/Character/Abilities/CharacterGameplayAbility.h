// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "E4GASModule.h"
#include "CharacterGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class E4GAS_API UCharacterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UCharacterGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EGASAbilityID AbilityID = EGASAbilityID::None;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
