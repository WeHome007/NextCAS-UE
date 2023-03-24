// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;
using System;

public class SampleNHSDKUE427Target : TargetRules
{
	public SampleNHSDKUE427Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		if(Target.Platform == UnrealTargetPlatform.Mac || Target.Platform == UnrealTargetPlatform.IOS) {
	        bOverrideBuildEnvironment = true;
	        AdditionalCompilerArguments = " -Wno-unused-but-set-variable";
		}

        ExtraModuleNames.AddRange( new string[] { "SampleNHSDKUE427" } );
	}
}
