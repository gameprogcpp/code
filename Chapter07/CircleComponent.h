// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#pragma once
#include "CollisionComponent.h"
#include "Math.h"

class CircleComponent : public CollisionComponent
{
public:
	CircleComponent(class Actor* owner);
	
	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const;
	
	const Vector3& GetCenter() const;
private:
	float mRadius;
};