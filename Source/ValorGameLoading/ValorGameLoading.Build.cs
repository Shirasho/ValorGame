// Copyright Shirasho Media 2016. All rights reserved.

using UnrealBuildTool;

public class ValorGameLoading : ModuleRules
{
    public ValorGameLoading(TargetInfo Target)
    {
        PrivateIncludePaths.Add("../../ValorGame/Source/ValorGameLoading/Private");

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "MoviePlayer",
                "Slate",
                "SlateCore",
                "InputCore"
            }
        );
    }
}
