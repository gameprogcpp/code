// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#include "PlayerMove.h"
#include "Actor.h"
#include "Game.h"
#include "PhysWorld.h"

PlayerMove::PlayerMove(Actor* owner)
	:MoveComponent(owner)
{
}

void PlayerMove::Update(float deltaTime)
{
	const float zOffset = 50.0f;
	const float segmentLength = 100.0f;
	PhysWorld* phys = mOwner->GetGame()->GetPhysWorld();

	// Test whether forward/strafe movement are valid
	// Start point is player position +z offset
	Vector3 start = mOwner->GetPosition();
	start.z += zOffset;
	// For forward/back
	if (!Math::NearZero(mForwardSpeed))
	{
		// End point is in direction of forward/backward vector
		Vector3 dir = mOwner->GetForward();
		if (mForwardSpeed < 0.0f)
		{
			dir *= -1.0f;
		}
		Vector3 end = start + dir * segmentLength;
		// Create line segment
		LineSegment l(start, end);
		// Test segment vs world
		PhysWorld::CollisionInfo info;
		if (phys->SegmentCast(l, info))
		{
			// If we collided, don't allow movement
			mForwardSpeed = 0.0f;
		}
	}
	// For strafing
	if (!Math::NearZero(mStrafeSpeed))
	{
		// End point is in direction of right/left vector
		Vector3 dir = mOwner->GetRight();
		if (mStrafeSpeed < 0.0f)
		{
			dir *= -1.0f;
		}
		Vector3 end = start + dir * segmentLength;
		// Create line segment
		LineSegment l(start, end);
		// Test segment vs world
		PhysWorld::CollisionInfo info;
		if (phys->SegmentCast(l, info))
		{
			// If we collided, don't allow movement
			mStrafeSpeed = 0.0f;
		}
	}

	// Now update move component based on modified speeds
	MoveComponent::Update(deltaTime);
}
