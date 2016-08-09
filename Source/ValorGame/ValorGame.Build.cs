// Copyright Shirasho Media 2016. All rights reserved.

using UnrealBuildTool;

public class ValorGame : ModuleRules
{
    public ValorGame(TargetInfo Target)
    {
        PublicIncludePaths.AddRange(new string[] {

        });

        PublicIncludePathModuleNames.AddRange(new string[] {

        });

        PrivateIncludePaths.AddRange(new string[] {
            "ValorGame/Private"
        });

        PrivateIncludePathModuleNames.AddRange(new string[] {
            "NetworkReplayStreaming"
        });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
            "AssetRegistry",
            "AIModule",
            "GameplayTasks",
            "Slate",
            "SlateCore",
            "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "InputCore",
            "ValorGameLoading",
            "Json",
            "OnlineSubsystem"
        });

        DynamicallyLoadedModuleNames.AddRange(new string[] {
            "OnlineSubsystemNull",
            "NetworkReplayStreaming",
            "NullNetworkReplayStreaming",
            "HttpNetworkReplayStreaming"
        });



        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Linux) || (Target.Platform == UnrealTargetPlatform.Mac))
        {
            if (UEBuildConfiguration.bCompileSteamOSS == true)
            {
                DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
            }
        }
        else if (Target.Platform == UnrealTargetPlatform.PS4)
        {
            DynamicallyLoadedModuleNames.Add("OnlineSubsystemPS4");
        }
        else if (Target.Platform == UnrealTargetPlatform.XboxOne)
        {
            DynamicallyLoadedModuleNames.Add("OnlineSubsystemLive");
        }
    }
}
