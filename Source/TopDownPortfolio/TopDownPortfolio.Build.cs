// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class TopDownPortfolio : ModuleRules
{
    public TopDownPortfolio(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" , "UMG",
           "EditorFramework", "Landscape" , "Foliage","Slate", "SlateCore", "LandscapeEditor", "UnrealEd", "AssetTools", "EditorSubsystem" //, "LandscapeEditorUtilities", 
        });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "EditorScriptingUtilities" });
    }
            
}
