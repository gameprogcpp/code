// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	
	bool Load(const std::string& fileName);
	void Unload();
	void CreateFromSurface(struct SDL_Surface* surface);
	void CreateForRendering(int width, int height, unsigned int format);
	
	void SetActive(int index = 0);
	
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
	unsigned int GetTextureID() const { return mTextureID; }
private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
};
