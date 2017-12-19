// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "NavComponent.h"
#include "Tile.h"

NavComponent::NavComponent(class Actor* owner, int updateOrder)
:MoveComponent(owner, updateOrder)
,mNextNode(nullptr)
{
	
}

void NavComponent::Update(float deltaTime)
{
	if (mNextNode)
	{
		// If we're at the next node, advance along path
		Vector2 diff = mOwner->GetPosition() - mNextNode->GetPosition();
		if (Math::NearZero(diff.Length(), 2.0f))
		{
			mNextNode = mNextNode->GetParent();
			TurnTo(mNextNode->GetPosition());
		}
	}
	
	MoveComponent::Update(deltaTime);
}

void NavComponent::StartPath(const Tile* start)
{
	mNextNode = start->GetParent();
	TurnTo(mNextNode->GetPosition());
}

void NavComponent::TurnTo(const Vector2& pos)
{
	// Vector from me to pos
	Vector2 dir = pos - mOwner->GetPosition();
	// New angle is just atan2 of this dir vector
	// (Negate y because +y is down on screen)
	float angle = Math::Atan2(-dir.y, dir.x);
	mOwner->SetRotation(angle);
}
