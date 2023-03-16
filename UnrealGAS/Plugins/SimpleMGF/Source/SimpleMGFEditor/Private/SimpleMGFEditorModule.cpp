// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleMGFEditorModule.h"

#define LOCTEXT_NAMESPACE "FSimpleMGFEditorModule"

void FSimpleMGFEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory;
	// the exact timing is specified in the .uplugin file per-module
}

void FSimpleMGFEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.
	// For modules that support dynamic reloading, we call this function before unloading the module.
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSimpleMGFEditorModule, SimpleMGFEditor)
