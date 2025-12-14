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
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UnrealEd",    // <--- Самое важное. Доступ к функционалу редактора.
				"GBAI",        // <--- Зависимость от нашего Runtime модуля, чтобы видеть его классы.
                "GameplayTags",
                "GameplayDebugger",
				"AIModule"
            }
        );
	}
}