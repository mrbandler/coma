// Copyright (c) fivefingergames GmbH. All rights reserved.

using UnrealBuildTool;

public class Coma : ModuleRules
{
	public Coma(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] {});
		PrivateIncludePaths.AddRange(new string[] {});
		PublicDependencyModuleNames.AddRange(new string[] { "Core" } );

        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine" });
        if (Target.Type == TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "BlueprintGraph" });
        }

        DynamicallyLoadedModuleNames.AddRange(new string[] {});
	}
}
