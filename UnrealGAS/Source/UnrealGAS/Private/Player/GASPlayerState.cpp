// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASPlayerState.h"

#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "GASGameplayTags.h"

AGASPlayerState::AGASPlayerState()
{
	// Set AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	
	// Mixed: Don't really care if other players are given like gameplay effects
	// We really only want to see like the cues meaning like the visual effects or the sound effect
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Set AttributeSetBase
	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("AttributeSetBase"));

	// Defaults to very low for PlayerStates and it might introduce some sort of perceived lag to the ability system
	NetUpdateFrequency = 100.0f;

	DeadTag = FGASGameplayTags::Get().State_Dead;
}

UAbilitySystemComponent* AGASPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCharacterAttributeSetBase* AGASPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool AGASPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void AGASPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	// Todo -- implement HUD Later
}

float AGASPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float AGASPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float AGASPlayerState::GetMana() const
{
	return AttributeSetBase->GetMana();
}

float AGASPlayerState::GetMaxMana() const
{
	return AttributeSetBase->GetMaxMana();
}

int32 AGASPlayerState::GetCharacterLevel() const
{
	return AttributeSetBase->GetLevel();
}

void AGASPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent)
	{
		// Set Attribute Changed Delegate
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AGASPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &AGASPlayerState::MaxHealthChanged);
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetManaAttribute()).AddUObject(this, &AGASPlayerState::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxManaAttribute()).AddUObject(this, &AGASPlayerState::MaxManaChanged);
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetLevelAttribute()).AddUObject(this, &AGASPlayerState::CharacterLevelChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGASGameplayTags::Get().State_Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AGASPlayerState::StunTagChanged);
	}
}

void AGASPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Health Changed!"))
}

void AGASPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("MaxHealth Changed!"))
}

void AGASPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Mana Changed!"))
}

void AGASPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("MaxMana Changed!"))
}

void AGASPlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Character Level Changed Changed!"))
}

void AGASPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if(NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGASGameplayTags::Get().Ability);

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGASGameplayTags::Get().Ability_NotCanceledByStun);

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
	UE_LOG(LogTemp, Warning, TEXT("Health Changed!"))
}
