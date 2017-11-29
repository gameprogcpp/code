// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// This corresponds to the output color
// to the color buffer
out vec4 outColor;

void main()
{
	// RGBA of 100% blue, 100% opaque
    outColor = vec4(0.0, 0.0, 1.0, 1.0);
}
