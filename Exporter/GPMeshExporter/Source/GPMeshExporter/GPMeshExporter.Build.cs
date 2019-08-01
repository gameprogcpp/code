// Some copyright should be here...

using UnrealBuildTool;

public class GPMeshExporter : ModuleRules
{
	public GPMeshExporter(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "Private/GPMeshExporterPrivatePCH.h";
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
                "Engine",
                "RenderCore",
                "UnrealEd",
                "ImageWrapper",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate", "SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
