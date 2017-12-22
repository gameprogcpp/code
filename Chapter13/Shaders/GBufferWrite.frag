// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330
// Inputs from vertex shader
// Tex coord
in vec2 fragTexCoord;
// Normal (in world space)
in vec3 fragNormal;
// Position (in world space)
in vec3 fragWorldPos;

// This corresponds to the outputs to the G-buffer
layout(location = 0) out vec3 outDiffuse;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out vec3 outWorldPos;

// This is used for the texture sampling
uniform sampler2D uTexture;

void main()
{
	// Diffuse color is sampled from texture
	outDiffuse = texture(uTexture, fragTexCoord).xyz;
	// Normal/world pos are passed directly along
	outNormal = fragNormal;
	outWorldPos = fragWorldPos;
}
