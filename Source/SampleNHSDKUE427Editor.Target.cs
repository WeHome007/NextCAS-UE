// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SampleNHSDKUE427EditorTarget : TargetRules
{
	public SampleNHSDKUE427EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		if(Target.Platform == UnrealTargetPlatform.IOS)
		{
            bOverrideBuildEnvironment = true;
            AdditionalCompilerArguments = "-Wno-unused-but-set-variable";
        }

        ExtraModuleNames.AddRange( new string[] { "SampleNHSDKUE427" } );
	}
}
