// Copyright Shirasho Media 2016. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ValorGameTarget : TargetRules
{
	public ValorGameTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "ValorGame" } );
	}

    public override List<UnrealTargetPlatform> GUBP_GetPlatforms_MonolithicOnly(UnrealTargetPlatform HostPlatform)
    {
        List<UnrealTargetPlatform> Platforms = null;

        switch (HostPlatform)
        {
            case UnrealTargetPlatform.Mac:
                Platforms = new List<UnrealTargetPlatform> { HostPlatform };
                break;

            case UnrealTargetPlatform.Win64:
                Platforms = new List<UnrealTargetPlatform> { HostPlatform, UnrealTargetPlatform.Win32, UnrealTargetPlatform.XboxOne, UnrealTargetPlatform.PS4 };
                break;

            default:
                Platforms = new List<UnrealTargetPlatform>();
                break;
        }

        return Platforms;
    }

    public override List<UnrealTargetConfiguration> GUBP_GetConfigs_MonolithicOnly(UnrealTargetPlatform HostPlatform, UnrealTargetPlatform Platform)
    {
        return new List<UnrealTargetConfiguration> { UnrealTargetConfiguration.Development };
    }

    public override List<GUBPFormalBuild> GUBP_GetConfigsForFormalBuilds_MonolithicOnly(UnrealTargetPlatform HostPlatform)
    {
        if (HostPlatform == UnrealTargetPlatform.Win64)
        {
            return new List<GUBPFormalBuild>
            {
                new GUBPFormalBuild(UnrealTargetPlatform.Linux, UnrealTargetConfiguration.Development),
                new GUBPFormalBuild(UnrealTargetPlatform.Win64, UnrealTargetConfiguration.Development),
                new GUBPFormalBuild(UnrealTargetPlatform.XboxOne, UnrealTargetConfiguration.Development),
                new GUBPFormalBuild(UnrealTargetPlatform.PS4, UnrealTargetConfiguration.Development),
            };
        }
        else
        {
            return new List<GUBPFormalBuild>
            {
                new GUBPFormalBuild(UnrealTargetPlatform.Mac, UnrealTargetConfiguration.Development),
            };
        }
    }
}
