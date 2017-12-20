// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

class SplineActor : public Actor
{
public:
	SplineActor(class Game* game);

	void ProcessInput(const uint8_t* keys) override;

	void RestartSpline();
private:
	class SplineCamera* mCameraComp;
};
