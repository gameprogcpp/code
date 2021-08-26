// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"

class PhysWorld
{
public:
	PhysWorld(class Game* game);

	// Used to give helpful information about collision results
	struct CollisionInfo
	{
		// Point of collision
		Vector3 mPoint;
		// Normal at collision
		Vector3 mNormal;
		// Component collided with
		class BoxComponent* mBox;
		// Owning actor of component
		class Actor* mActor;
	};

	// Test a line segment against boxes
	// Returns true if it collides against a box
	bool SegmentCast(const LineSegment& l, CollisionInfo& outColl);

	// Tests collisions using naive pairwise
	void TestPairwise(std::function<void(class Actor*, class Actor*)> f);
	// Test collisions using sweep and prune
	void TestSweepAndPrune(std::function<void(class Actor*, class Actor*)> f);

	// Add/remove box components from world
	void AddBox(class BoxComponent* box);
	void RemoveBox(class BoxComponent* box);
private:
	class Game* mGame;
	std::vector<class BoxComponent*> mBoxes;
};
