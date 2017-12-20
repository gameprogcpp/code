// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

class OrbitActor : public Actor
{
public:
	OrbitActor(class Game* game);

	void ProcessInput(const uint8_t* keys) override;

	void SetVisible(bool visible);
private:
	class OrbitCamera* mCameraComp;
	class MeshComponent* mMeshComp;
};
