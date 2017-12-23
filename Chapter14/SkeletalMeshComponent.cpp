// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SkeletalMeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Animation.h"
#include "Skeleton.h"
#include "LevelLoader.h"

SkeletalMeshComponent::SkeletalMeshComponent(Actor* owner)
	:MeshComponent(owner, true)
	,mSkeleton(nullptr)
{
}

void SkeletalMeshComponent::Draw(Shader* shader)
{
	if (mMesh)
	{
		// Set the world transform
		shader->SetMatrixUniform("uWorldTransform", 
			mOwner->GetWorldTransform());
		// Set the matrix palette
		shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0], 
			MAX_SKELETON_BONES);
		// Set specular power
		shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
		// Set the active texture
		Texture* t = mMesh->GetTexture(mTextureIndex);
		if (t)
		{
			t->SetActive();
		}
		// Set the mesh's vertex array as active
		VertexArray* va = mMesh->GetVertexArray();
		va->SetActive();
		// Draw
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void SkeletalMeshComponent::Update(float deltaTime)
{
	if (mAnimation && mSkeleton)
	{
		mAnimTime += deltaTime * mAnimPlayRate;
		// Wrap around anim time if past duration
		while (mAnimTime > mAnimation->GetDuration())
		{
			mAnimTime -= mAnimation->GetDuration();
		}

		// Recompute matrix palette
		ComputeMatrixPalette();
	}
}

float SkeletalMeshComponent::PlayAnimation(Animation* anim, float playRate)
{
	mAnimation = anim;
	mAnimTime = 0.0f;
	mAnimPlayRate = playRate;

	if (!mAnimation) { return 0.0f; }

	ComputeMatrixPalette();

	return mAnimation->GetDuration();
}

void SkeletalMeshComponent::LoadProperties(const rapidjson::Value& inObj)
{
	MeshComponent::LoadProperties(inObj);

	std::string skelFile;
	if (JsonHelper::GetString(inObj, "skelFile", skelFile))
	{
		SetSkeleton(mOwner->GetGame()->GetSkeleton(skelFile));
	}

	std::string animFile;
	if (JsonHelper::GetString(inObj, "animFile", animFile))
	{
		PlayAnimation(mOwner->GetGame()->GetAnimation(animFile));
	}

	JsonHelper::GetFloat(inObj, "animPlayRate", mAnimPlayRate);
	JsonHelper::GetFloat(inObj, "animTime", mAnimTime);
}

void SkeletalMeshComponent::SaveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	MeshComponent::SaveProperties(alloc, inObj);

	if (mSkeleton)
	{
		JsonHelper::AddString(alloc, inObj, "skelFile", mSkeleton->GetFileName());
	}

	if (mAnimation)
	{
		JsonHelper::AddString(alloc, inObj, "animFile", mAnimation->GetFileName());
	}

	JsonHelper::AddFloat(alloc, inObj, "animPlayRate", mAnimPlayRate);
	JsonHelper::AddFloat(alloc, inObj, "animTime", mAnimTime);
}

void SkeletalMeshComponent::ComputeMatrixPalette()
{
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	std::vector<Matrix4> currentPoses;
	mAnimation->GetGlobalPoseAtTime(currentPoses, mSkeleton, mAnimTime);

	// Setup the palette for each bone
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		// Global inverse bind pose matrix times current pose matrix
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}
