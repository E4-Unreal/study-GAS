// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SimpleMGFGame : ModuleRules
{
	public SimpleMGFGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				// Default Modules
				"Core",
				
				// Additional Modules
				"EnhancedInput"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// Default Modules
				"CoreUObject",
				"Engine",

				// Additional Modules
				//// Native Gameplay Tags
				"SimpleMGFGameplayTags",
				"GameplayTags",
				//// Gameplay Ability System
				"GameplayAbilities",
				"GameplayTasks",
				//// Modular Gameplay Features
				"ModularGameplay",
				"GameFeatures",
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// Additional Modules
			}
			);
	}
}
