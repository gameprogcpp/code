// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Mesh.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include <rapidjson/document.h>
#include <SDL/SDL_log.h>
#include "Math.h"
#include "LevelLoader.h"
#include <fstream>

namespace
{
	union Vertex
	{
		float f;
		uint8_t b[4];
	};

	const int BinaryVersion = 1;
	struct MeshBinHeader
	{
		// Signature for file type
		char mSignature[4] = { 'G', 'M', 'S', 'H' };
		// Version
		uint32_t mVersion = BinaryVersion;
		// Vertex layout type
		VertexArray::Layout mLayout = VertexArray::PosNormTex;
		// Info about how many of each we have
		uint32_t mNumTextures = 0;
		uint32_t mNumVerts = 0;
		uint32_t mNumIndices = 0;
		// Box/radius of mesh, used for collision
		AABB mBox{ Vector3::Zero, Vector3::Zero };
		float mRadius = 0.0f;
		float mSpecPower = 100.0f;
	};
}

Mesh::Mesh()
	:mBox(Vector3::Infinity, Vector3::NegInfinity)
	,mVertexArray(nullptr)
	,mRadius(0.0f)
	,mSpecPower(100.0f)
{
}

Mesh::~Mesh()
{
}

bool Mesh::Load(const std::string& fileName, Renderer* renderer)
{
	mFileName = fileName;

	// Try loading the binary file first
	if (LoadBinary(fileName + ".bin", renderer))
	{
		return true;
	}

	rapidjson::Document doc;
	if (!LevelLoader::LoadJSON(fileName, doc))
	{
		SDL_Log("Failed to load mesh %s", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the version
	if (ver != 1)
	{
		SDL_Log("Mesh %s not version 1", fileName.c_str());
		return false;
	}

	mShaderName = doc["shader"].GetString();

	// Set the vertex layout/size based on the format in the file
	VertexArray::Layout layout = VertexArray::PosNormTex;
	size_t vertSize = 8;

	std::string vertexFormat = doc["vertexformat"].GetString();
	if (vertexFormat == "PosNormSkinTex")
	{
		layout = VertexArray::PosNormSkinTex;
		// This is the number of "Vertex" unions, which is 8 + 2 (for skinning)s
		vertSize = 10;
	}

	// Load textures
	const rapidjson::Value& textures = doc["textures"];
	if (!textures.IsArray() || textures.Size() < 1)
	{
		SDL_Log("Mesh %s has no textures, there should be at least one", fileName.c_str());
		return false;
	}

	mSpecPower = static_cast<float>(doc["specularPower"].GetDouble());

	std::vector<std::string> textureNames;
	for (rapidjson::SizeType i = 0; i < textures.Size(); i++)
	{
		// Is this texture already loaded?
		std::string texName = textures[i].GetString();
		textureNames.emplace_back(texName);
		Texture* t = renderer->GetTexture(texName);
		if (t == nullptr)
		{
			// If it's null, use the default texture
			t = renderer->GetTexture("Assets/Default.png");
		}
		mTextures.emplace_back(t);
	}

	// Load in the vertices
	const rapidjson::Value& vertsJson = doc["vertices"];
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no vertices", fileName.c_str());
		return false;
	}

	std::vector<Vertex> vertices;
	vertices.reserve(vertsJson.Size() * vertSize);
	mRadius = 0.0f;
	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
	{
		// For now, just assume we have 8 elements
		const rapidjson::Value& vert = vertsJson[i];
		if (!vert.IsArray())
		{
			SDL_Log("Unexpected vertex format for %s", fileName.c_str());
			return false;
		}

		Vector3 pos(vert[0].GetDouble(), vert[1].GetDouble(), vert[2].GetDouble());
		mRadius = Math::Max(mRadius, pos.LengthSq());
		mBox.UpdateMinMax(pos);

		if (layout == VertexArray::PosNormTex)
		{
			Vertex v;
			// Add the floats
			for (rapidjson::SizeType j = 0; j < vert.Size(); j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}
		}
		else
		{
			Vertex v;
			// Add pos/normal
			for (rapidjson::SizeType j = 0; j < 6; j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}

			// Add skin information
			for (rapidjson::SizeType j = 6; j < 14; j += 4)
			{
				v.b[0] = vert[j].GetUint();
				v.b[1] = vert[j + 1].GetUint();
				v.b[2] = vert[j + 2].GetUint();
				v.b[3] = vert[j + 3].GetUint();
				vertices.emplace_back(v);
			}

			// Add tex coords
			for (rapidjson::SizeType j = 14; j < vert.Size(); j++)
			{
				v.f = vert[j].GetDouble();
				vertices.emplace_back(v);
			}
		}
	}

	// We were computing length squared earlier
	mRadius = Math::Sqrt(mRadius);

	// Load in the indices
	const rapidjson::Value& indJson = doc["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no indices", fileName.c_str());
		return false;
	}

	std::vector<unsigned int> indices;
	indices.reserve(indJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
	{
		const rapidjson::Value& ind = indJson[i];
		if (!ind.IsArray() || ind.Size() != 3)
		{
			SDL_Log("Invalid indices for %s", fileName.c_str());
			return false;
		}

		indices.emplace_back(ind[0].GetUint());
		indices.emplace_back(ind[1].GetUint());
		indices.emplace_back(ind[2].GetUint());
	}

	// Now create a vertex array
	unsigned int numVerts = static_cast<unsigned>(vertices.size()) / vertSize;
	mVertexArray = new VertexArray(vertices.data(), numVerts,
		layout, indices.data(), static_cast<unsigned>(indices.size()));

	// Save the binary mesh
	SaveBinary(fileName + ".bin", vertices.data(),
		numVerts, layout, indices.data(),
		static_cast<unsigned>(indices.size()),
		textureNames, mBox, mRadius,
		mSpecPower);
	return true;
}

void Mesh::Unload()
{
	delete mVertexArray;
	mVertexArray = nullptr;
}

Texture* Mesh::GetTexture(size_t index)
{
	if (index < mTextures.size())
	{
		return mTextures[index];
	}
	else
	{
		return nullptr;
	}
}

void Mesh::SaveBinary(const std::string& fileName, const void* verts, 
	uint32_t numVerts, VertexArray::Layout layout,
	const uint32_t* indices, uint32_t numIndices,
	const std::vector<std::string>& textureNames,
	const AABB& box, float radius,
	float specPower)
{
	// Create header struct
	MeshBinHeader header;
	header.mLayout = layout;
	header.mNumTextures = 
		static_cast<unsigned>(textureNames.size());
	header.mNumVerts = numVerts;
	header.mNumIndices = numIndices;
	header.mBox = box;
	header.mRadius = radius;

	// Open binary file for writing
	std::ofstream outFile(fileName, std::ios::out 
		| std::ios::binary);
	if (outFile.is_open())
	{
		// Write the header
		outFile.write(reinterpret_cast<char*>(&header), sizeof(header));

		// For each texture, we need to write the size of the name
		// followed by the string (null-terminated)
		for (const auto& tex : textureNames)
		{
			// (Assume file names won't have more than 32k characters)
			uint16_t nameSize = static_cast<uint16_t>(tex.length()) + 1;
			outFile.write(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
			outFile.write(tex.c_str(), nameSize - 1);
			outFile.write("\0", 1);
		}

		// Figure out number of bytes for each vertex, based on layout
		unsigned vertexSize = VertexArray::GetVertexSize(layout);
		// Write vertices
		outFile.write(reinterpret_cast<const char*>(verts), 
			numVerts * vertexSize);
		// Write indices
		outFile.write(reinterpret_cast<const char*>(indices), 
			numIndices * sizeof(uint32_t));
	}
}

bool Mesh::LoadBinary(const std::string& fileName, Renderer* renderer)
{
	std::ifstream inFile(fileName, std::ios::in | 
		std::ios::binary);
	if (inFile.is_open())
	{
		// Read in header
		MeshBinHeader header;
		inFile.read(reinterpret_cast<char*>(&header), sizeof(header));

		// Validate the header signature and version
		char* sig = header.mSignature;
		if (sig[0] != 'G' || sig[1] != 'M' || sig[2] != 'S' ||
			sig[3] != 'H' || header.mVersion != BinaryVersion)
		{
			return false;
		}

		// Read in the texture file names
		for (uint32_t i = 0; i < header.mNumTextures; i++)
		{
			// Get the file name size
			uint16_t nameSize = 0;
			inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
			
			// Make a buffer of this size
			char* texName = new char[nameSize];
			// Read in the texture name
			inFile.read(texName, nameSize);
			
			// Get this texture
			Texture* t = renderer->GetTexture(texName);
			if (t == nullptr)
			{
				// If it's null, use the default texture
				t = renderer->GetTexture("Assets/Default.png");
			}
			mTextures.emplace_back(t);

			delete[] texName;
		}

		// Now read in the vertices
		unsigned vertexSize = VertexArray::GetVertexSize(header.mLayout);
		char* verts = new char[header.mNumVerts * vertexSize];
		inFile.read(verts, header.mNumVerts * vertexSize);

		// Now read in the indices
		uint32_t* indices = new uint32_t[header.mNumIndices];
		inFile.read(reinterpret_cast<char*>(indices), 
			header.mNumIndices * sizeof(uint32_t));

		// Now create the vertex array
		mVertexArray = new VertexArray(verts, header.mNumVerts,
			header.mLayout, indices, header.mNumIndices);

		// Cleanup memory
		delete[] verts;
		delete[] indices;

		// Set mBox/mRadius/specular from header
		mBox = header.mBox;
		mRadius = header.mRadius;
		mSpecPower = header.mSpecPower;

		return true;
	}
	return false;
}
