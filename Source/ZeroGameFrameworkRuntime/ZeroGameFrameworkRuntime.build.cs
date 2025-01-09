// Copyright Zero Games. All Rights Reserved.

using UnrealBuildTool;

public class ZeroGameFrameworkRuntime : ModuleRules
{
	public ZeroGameFrameworkRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange
		(
			new string[]
			{
			}
		);
		
		PrivateIncludePaths.AddRange
		(
			new string[]
			{
			}
		);
		
		PublicDependencyModuleNames.AddRange
		(
			new string[]
			{
				"Core",
			}
		);
		
		PrivateDependencyModuleNames.AddRange
		(
			new string[]
			{
				"CoreUObject",
				"GameplayTags",
				"EnhancedInput",
				"Engine",
				"AIModule",
				
				"ZSharpRuntime",
				"ZeroExtensionSystemRuntime",
			}
		);
		
		DynamicallyLoadedModuleNames.AddRange
		(
			new string[]
			{
			}
		);
	}
}


