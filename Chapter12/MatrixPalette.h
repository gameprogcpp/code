// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Math.h"

const size_t MAX_SKELETON_BONES = 96;

struct MatrixPalette
{
	Matrix4 mEntry[MAX_SKELETON_BONES];
};
