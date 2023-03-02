using UnrealBuildTool; 

public class E4GAS: ModuleRules 
{ 
	public E4GAS(ReadOnlyTargetRules Target) : base(Target) 
	{
		// Default Modules
		PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"});
		
		// Additional Modules for GAS
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"AIModule"
		});
	} 
}