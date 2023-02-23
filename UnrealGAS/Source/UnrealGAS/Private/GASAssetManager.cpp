// Fill out your copyright notice in the Description page of Project Settings.

#include "GASAssetManager.h"
#include "GASGameplayTags.h"
#include "AbilitySystemGlobals.h"

void UGASAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FGASGameplayTags::InitializeNativeTags();
	
	UAbilitySystemGlobals::Get().InitGlobalData();
}
