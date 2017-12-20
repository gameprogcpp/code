// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
class CollisionComponent : public Component
{
public:
	CollisionComponent(class Actor* owner, int updateOrder = 100);
	~CollisionComponent();
};

