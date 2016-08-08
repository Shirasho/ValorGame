// Copyright Shirasho Media 2016. All rights reserved.

using UnrealBuildTool;

public class ValorGameEditor : ModuleRules
{
    public ValorGameEditor(TargetInfo Target)
    {
        PublicIncludePaths.AddRange(new string[] {
            "ValorGameEditor",
            "ValorGameEditor/Public"
        });

        PublicIncludePathModuleNames.AddRange(new string[] {

        });

        PrivateIncludePaths.AddRange(new string[] {
            "ValorGameEditor/Private"
        });

        PrivateIncludePathModuleNames.AddRange(new string[] {

        });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "ValorGame"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "CoreUObject",
            "InputCore",
            "Slate",
            "Engine",
            "AssetTools",
            "UnrealEd", // for FAssetEditorManager
            "KismetWidgets",
            "KismetCompiler",
            "BlueprintGraph",
            "GraphEditor",
            "Kismet",  // for FWorkflowCentricApplication
            "PropertyEditor",
            "EditorStyle",
            "Slate",
            "SlateCore",
            "Sequencer",
            "DetailCustomizations",
            "Settings",
            "RenderCore"
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
