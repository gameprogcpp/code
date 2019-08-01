# Game Programming in C++ Unreal Engine 4 Exporter
This plugin allows you to export static meshes, skeletal meshes, skeletons, and animations
from the Unreal Engine 4 format into the Game Programming in C++ format.

This plugin has been verified to work in Unreal Engine 4.22.3. It likely will work in versions
as early as Unreal Engine 4.19.x, though it has not been tested.

This code is free to use, but the copyright of the code is maintained by Epic Games, and you
must agree to the Unreal Engine license separately in order to use this plugin.

# Using the plugin
To use this plugin, follow these steps:
1. Make sure the Unreal 4 project you want to use is setup to work with C++
2. In the C++ Unreal 4 project directory, create a "Plugins" directory
3. Place the "GPMeshExporter" directory inside "Plugins"
4. Right click on your .uproject and regenerate the project files
5. Now in the editor, you can right click on a static mesh and select
   "Asset Actions>Export...". From the file dropdown, select
   .gpmesh. Similarly, you can export skeletal meshes to .gpmesh and
   animations to .gpanim.

##A Note on Mesh Orientation
The plug-in does not fix-up or transform the asset in any way. You
should make sure your asset is facing down the X-axis with Z-up
before you export it.

##A Note on Textures
Right now, the exporter will select the FIRST texture associated with
the "BaseColor" of the FIRST material assigned to the mesh. Multiple
materials/textures will be ignored.

Also, the exporter assumes that you will follow the convention where the texture
file is in Assets/NameOfTexture. So when it exports, you'll get both
an .gpmesh and a .bmp file in the same directory, place both files in the
Assets directory of the Game Programming in C++ project.

## A Note on Shaders
By default, static meshes will be exported and refer to the "BasicMesh"
shader. If you want to change this, for now you have to just manually edit
the .gpmesh file to change the shader. Similarly, SkeletalMeshes will
export referring to the "Skinned" shader.

##A Note on Skeletal Meshes/Skeletons and Animations
Skeletal Meshes will export their textures as static meshes do, and will
additionally export a .gpskel file in the same directory as the skeletal
mesh exports.

For animations, it is assumed that there is no scale applied -- bones
only export their rotation and translation.
