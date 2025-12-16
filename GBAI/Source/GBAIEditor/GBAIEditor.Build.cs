using UnrealBuildTool;

public class GBAIEditor : ModuleRules
{
	public GBAIEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject", "Engine",  // Core
				"UnrealEd", "GBAI", "GameplayDebugger", "AIModule"  // Custom
            }
        );
	}
}