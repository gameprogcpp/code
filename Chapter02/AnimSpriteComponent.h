// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <map>
#include <string>
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// Update animation every frame (overridden from component)
	void Update(float deltaTime) override;
	// Set the textures used for animation: clear current textures
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures, std::string animName, bool isLoop);
	// Add the textures used for animation: add to current textures
	void AddAnimTextures(const std::vector<SDL_Texture*>& textures, std::string animName, bool isLoop);
	// Set the animation displayed
	void SetUseAnimation(std::string animName) { mCurrAnim = animName; };
	// Set/get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	// Set whether animation loop of current animation
	void SetIsLoop(bool isLoop) { mAnimations[mCurrAnim].isLoop = isLoop; }
private:
	// All textures in all animations
	std::vector<SDL_Texture*> mAnimTextures;

	// 各アニメーション
	struct Animation {
		// start Index of mAnimTextures
		int startIndex;
		// number of texture
		int count;
		// whether animatnion loop
		bool isLoop;
	};
	// All animations
	std::map<std::string, Animation> mAnimations;

	// Current animation name 
	std::string mCurrAnim; 
	// Current frame displayed
	float mCurrFrame;
	// Animation frame rate
	float mAnimFPS;
};
