// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

class CameraActor : public Actor
{
public:
	CameraActor(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ProcessInput(const uint8_t* keys) override;
private:
	class MoveComponent* mMoveComp;
};