// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AnimSpriteComponent.h"
#include "Math.h"
#include <iostream>
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
		
		
		// Wrap current frame if needed
		while (mCurrFrame >= mAnimCount[mCurrAnim])
		{
			if (mAnimIsLoop[mCurrAnim])
			{
				mCurrFrame -= mAnimCount[mCurrAnim];

			}
			else {
				mCurrFrame = mAnimCount[mCurrAnim] - 1;
			}
		}

		// Set the current texture
		// consider the start index of target animation
		int index = static_cast<int>(mCurrFrame) + mAnimStartIdx[mCurrAnim];
		SetTexture(mAnimTextures[index]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures, std::string animName, bool isLoop)
{
	mAnimTextures = textures;
	mAnimStartIdx.clear();
	mAnimCount.clear();
	mAnimIsLoop.clear();
	mAnimStartIdx[animName] = 0;
	mAnimCount[animName] = static_cast<int>(mAnimTextures.size());
	mAnimIsLoop[animName] = isLoop;
		
	if (mAnimTextures.size() > 0)
	{
		// Set the given animation active
		mCurrAnim = animName;

		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}

void AnimSpriteComponent::AddAnimTextures(const std::vector<SDL_Texture*>& textures, std::string animName, bool isLoop)
{
	// TODO: nameの重複の確認
	mAnimStartIdx[animName] = static_cast<int>(mAnimTextures.size());
	mAnimCount[animName] = static_cast<int>(textures.size());
	mAnimIsLoop[animName] = isLoop;
	// テクスチャの連結
	//mAnimTextures.insert(mAnimTextures.end(), textures.begin(), textures.end()); // うまく行かない
	mAnimTextures.reserve(mAnimTextures.size() + textures.size());
	std::copy(textures.begin(), textures.end(), std::back_inserter(mAnimTextures));

}

void AnimSpriteComponent::runAnimation(std::string animName)
{
	// 前のアニメーションとの整合性は考えない
// error処理: animNameが存在しない場合

	if (mCurrAnim != animName && mAnimCount[animName] > 0)
	{
		mCurrAnim = animName;
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[mAnimStartIdx[animName]]);
	}
}

