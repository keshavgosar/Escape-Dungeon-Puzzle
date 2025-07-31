// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EscapeTimeLoop : ModuleRules
{
	public EscapeTimeLoop(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
