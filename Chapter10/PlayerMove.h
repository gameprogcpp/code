// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "MoveComponent.h"

class PlayerMove : public MoveComponent
{
public:
	PlayerMove(class Actor* owner);

	void Update(float deltaTime) override;
protected:
};