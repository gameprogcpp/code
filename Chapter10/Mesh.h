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

class Mesh
{
public:
	Mesh();
	~Mesh();
	// Load/unload mesh
	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();
	// Get the vertex array associated with this mesh
	class VertexArray* GetVertexArray() { return mVertexArray; }
	// Get a texture from specified index
	class Texture* GetTexture(size_t index);
	// Get name of shader
	const std::string& GetShaderName() const { return mShaderName; }
	// Get object space bounding sphere radius
	float GetRadius() const { return mRadius; }
	// Get object space bounding box
	const AABB& GetBox() const { return mBox; }
	// Get specular power of mesh
	float GetSpecPower() const { return mSpecPower; }
private:
	// AABB collision
	AABB mBox;
	// Textures associated with this mesh
	std::vector<class Texture*> mTextures;
	// Vertex array associated with this mesh
	class VertexArray* mVertexArray;
	// Name of shader specified by mesh
	std::string mShaderName;
	// Stores object space bounding sphere radius
	float mRadius;
	// Specular power of surface
	float mSpecPower;
};