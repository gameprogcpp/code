// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "BoneTransform.h"
#include <vector>
#include <string>

class Animation
{
public:
	bool Load(const std::string& fileName);

	size_t GetNumBones() const { return mNumBones; }
	size_t GetNumFrames() const { return mNumFrames; }
	float GetDuration() const { return mDuration; }
	float GetFrameDuration() const { return mFrameDuration; }

	// Fills the provided vector with the global (current) pose matrices for each
	// bone at the specified time in the animation. It is expected that the time
	const std::string& GetFileName() const { return mFileName; }
	// is >= 0.0f and <= mDuration
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;
private:
	// Number of bones for the animation
	size_t mNumBones;
	// Number of frames in the animation
	size_t mNumFrames;
	// Duration of the animation in seconds
	float mDuration;
	// Duration of each frame in the animation
	float mFrameDuration;
	// Transform information for each frame on the track
	// Each index in the outer vector is a bone, inner vector
	// is a frame
	std::vector<std::vector<BoneTransform>> mTracks;
	std::string mFileName;
};
