// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Animation/AnimInstance.h"
#include "GameplayEffectTypes.h" // for FGameplayTagBlueprintPropertyMap
#include "SimpleMGFGameAnimInstance.generated.h"

class UAbilitySystemComponent;

UCLASS()
class USimpleMGFGameAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

public:
	//~ Begin UAnimInstance interface
	virtual void NativeInitializeAnimation() override;
	//~ End UAnimInstance interface

	void InitializeWithAbilitySystem(UAbilitySystemComponent* AbilityComponent);

	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Initialize with Ability System")
	void ReceiveAbilitySystem(UAbilitySystemComponent* AbilitySystem);
};
