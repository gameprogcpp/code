// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class Actor* owner)
:CollisionComponent(owner)
,mRadius(0.0f)
{
	
}

const Vector3& CircleComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}
