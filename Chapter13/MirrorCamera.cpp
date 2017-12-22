// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MirrorCamera.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

MirrorCamera::MirrorCamera(Actor* owner)
	:CameraComponent(owner)
	,mHorzDist(150.0f)
	,mVertDist(200.0f)
	,mTargetDist(400.0f)
{
}

void MirrorCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	// Compute ideal position
	Vector3 idealPos = ComputeCameraPos();
	// Target is target dist in front of owning actor
	Vector3 target = mOwner->GetPosition() -
		mOwner->GetForward() * mTargetDist;
	// Use actual position here, not ideal
	Matrix4 view = Matrix4::CreateLookAt(idealPos, target,
		Vector3::UnitZ);
	Game* game = mOwner->GetGame();
	game->GetRenderer()->SetMirrorView(view);
}

void MirrorCamera::SnapToIdeal()
{
	Vector3 idealPos = ComputeCameraPos();
	// Compute target and view
	Vector3 target = mOwner->GetPosition() -
		mOwner->GetForward() * mTargetDist;
	// Use actual position here, not ideal
	Matrix4 view = Matrix4::CreateLookAt(idealPos, target,
		Vector3::UnitZ);
	Game* game = mOwner->GetGame();
	game->GetRenderer()->SetMirrorView(view);
}

Vector3 MirrorCamera::ComputeCameraPos() const
{
	// Set camera position in front of
	Vector3 cameraPos = mOwner->GetPosition();
	cameraPos += mOwner->GetForward() * mHorzDist;
	cameraPos += Vector3::UnitZ * mVertDist;
	return cameraPos;
}
