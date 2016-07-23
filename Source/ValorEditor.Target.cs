// Copyright Shirasho Media 2016. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ValorEditorTarget : TargetRules
{
	public ValorEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;
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
}
