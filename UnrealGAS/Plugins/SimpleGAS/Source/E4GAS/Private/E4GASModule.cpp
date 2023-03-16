#include "E4GASModule.h"

#include "AbilitySystemGlobals.h"
#include "GASGameplayTags.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FTemplateModule"

// Instead of UGASAssetManager::StartInitialLoading()
void FE4GASModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FGASGameplayTags::InitializeNativeTags();
	//UAbilitySystemGlobals::Get().InitGlobalData();
}

void FE4GASModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FE4GASModule, E4GAS);