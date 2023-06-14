// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;
using System;

public class DemoTarget : TargetRules
{
	public DemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		if(Target.Platform == UnrealTargetPlatform.Mac || Target.Platform == UnrealTargetPlatform.IOS) {
	        bOverrideBuildEnvironment = true;
	        AdditionalCompilerArguments = " -Wno-unused-but-set-variable";
		}

        ExtraModuleNames.AddRange( new string[] { "Demo" } );
	}
}
