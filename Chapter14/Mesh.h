// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include <string>
#include "Collision.h"
#include "VertexArray.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	// Load/unload mesh
	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();
	// Get the vertex array associated with this mesh
	VertexArray* GetVertexArray() { return mVertexArray; }
	// Get a texture from specified index
	class Texture* GetTexture(size_t index);
	// Get name of shader
	const std::string& GetShaderName() const { return mShaderName; }
	// Get file name
	const std::string& GetFileName() const { return mFileName; }
	// Get object space bounding sphere radius
	float GetRadius() const { return mRadius; }
	// Get object space bounding box
	const AABB& GetBox() const { return mBox; }
	// Get specular power of mesh
	float GetSpecPower() const { return mSpecPower; }

	// Save the mesh in binary format
	void SaveBinary(const std::string& fileName, const void* verts, 
		uint32_t numVerts, VertexArray::Layout layout,
		const uint32_t* indices, uint32_t numIndices,
		const std::vector<std::string>& textureNames,
		const AABB& box, float radius,
		float specPower);
	// Load in the mesh from binary format
	bool LoadBinary(const std::string& fileName, class Renderer* renderer);
private:
	// AABB collision
	AABB mBox;
	// Textures associated with this mesh
	std::vector<class Texture*> mTextures;
	// Vertex array associated with this mesh
	VertexArray* mVertexArray;
	// Name of shader specified by mesh
	std::string mShaderName;
	// Name of mesh file
	std::string mFileName;
	// Stores object space bounding sphere radius
	float mRadius;
	// Specular power of surface
	float mSpecPower;
};