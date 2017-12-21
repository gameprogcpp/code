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
	// Move component does (forward/strafe/rotate)
	MoveComponent::Update(deltaTime);

	// Test my AABB versus every plane
}
