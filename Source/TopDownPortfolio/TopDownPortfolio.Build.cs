// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDownPortfolio : ModuleRules
{
	public TopDownPortfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" , "UMG",
            "UnrealEd", "EditorFramework", "Landscape" , "Foliage","Slate", "SlateCore", "LandscapeEditor",//, "LandscapeEditorUtilities"
        });

        if(Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"});
        }
    }
            
}
