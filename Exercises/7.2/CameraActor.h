// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include "SoundEvent.h"

class CameraActor : public Actor
{
public:
	CameraActor(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keys) override;

	void SetFootstepSurface(float value);
	const Vector3& GetCameraPosition() const { return mCameraPos; }
private:
	class MoveComponent* mMoveComp;
	class AudioComponent* mAudioComp;
	Vector3 mCameraPos;
	SoundEvent mFootstep;
	float mLastFootstep;
};