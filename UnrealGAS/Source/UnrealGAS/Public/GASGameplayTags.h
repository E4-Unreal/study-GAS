// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

// Singleton containing native gameplay tags.
struct UNREALGAS_API FGASGameplayTags
{
public:
	static const FGASGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	// State Tag
	FGameplayTag State_Dead;
	FGameplayTag State_Debuff_Stun;
	FGameplayTag State_RemoveOnDeath;

	// Ability Tag
	FGameplayTag Ability;
	FGameplayTag Ability_NotCanceledByStun;

	// Input Tags
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look;
	FGameplayTag InputTag_Jump;

protected:
	//Registers all of the tags with the GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FGASGameplayTags GameplayTags;
};