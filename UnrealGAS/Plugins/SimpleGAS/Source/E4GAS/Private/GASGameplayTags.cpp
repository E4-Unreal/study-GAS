// Fill out your copyright notice in the Description page of Project Settings.

#include "GASGameplayTags.h"
#include "GameplayTagsManager.h"
#include "Engine/EngineTypes.h"

// Convert VariableName to TagName
// ex) FGameplayTag Item_Equipment > "Item.Equipment"
#define ADD_TAG(VariableName, TagComment) AddTag(VariableName, TCHAR_TO_ANSI(*FString(# VariableName).Replace(TEXT("_"), TEXT("."))), TagComment)

FGASGameplayTags FGASGameplayTags::GameplayTags;

void FGASGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}

void FGASGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	// State Tag
	ADD_TAG(State_Dead, "Dead State");
	ADD_TAG(State_Debuff_Stun, "Stun Debuff State");
	ADD_TAG(State_RemoveOnDeath, "RemoveOnDeath State");

	// Ability Tag
	ADD_TAG(Ability, "Ability");
	ADD_TAG(Ability_NotCanceledByStun, "Not Canceled By Stun Ability");

	// Input Tags
	ADD_TAG(InputTag_Move, "Move input.");
	ADD_TAG(InputTag_Look, "Look input.");
	ADD_TAG(InputTag_Jump, "Jump input");
	ADD_TAG(InputTag_Test, "Test input");
}

// Todo OutTag의 변수명을 분석하여 TagName을 자동으로 추가하는 기능 필요
void FGASGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
