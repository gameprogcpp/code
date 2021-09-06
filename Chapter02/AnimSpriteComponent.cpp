// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;
		
		Animation anim = mAnimations[mCurrAnim];
		// Wrap current frame if needed
		while (mCurrFrame >= anim.count)
		{
			if (anim.isLoop)
			{
				mCurrFrame -= anim.count;

			}
			else {
				mCurrFrame = anim.count - 1;
			}
		}

		// Set the current texture
		// consider the start index of target animation
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame) + anim.startIndex]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures, std::string animName, bool isLoop)
{
	mAnimTextures = textures;
	Animation anim{ 0, mAnimTextures.size(), isLoop};
	mAnimations.clear();
	// TODO: nameの重複の確認
	mAnimations.emplace(animName, anim);
	if (mAnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);

		// Set the given animation active
		mCurrAnim = animName;
	}
}


void AnimSpriteComponent::AddAnimTextures(const std::vector<SDL_Texture*>& textures, std::string animName, bool isLoop)
{
	Animation anim{ mAnimTextures.size() - 1, textures.size(), isLoop };
	mAnimations.emplace(animName, anim);
	// テクスチャの連結
	mAnimTextures.insert(mAnimTextures.end(), textures.begin(), textures.end());

}