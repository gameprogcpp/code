// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// Uniforms for world transform and view-proj
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// Attribute 0 is position, 1 is normal, 2 is tex coords.
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

// Any vertex outputs (other than position)
out vec2 fragTexCoord;
// Normal (in world space)
out vec3 fragNormal;
// Position (in world space)
out vec3 fragWorldPos;

void main()
{
	// Convert position to homogeneous coordinates
	vec4 pos = vec4(inPosition, 1.0);
	// Transform position to world space
	pos = pos * uWorldTransform;
	// Save world position
	fragWorldPos = pos.xyz;
	// Transform to clip space
	gl_Position = pos * uViewProj;

	// Transform normal into world space (w = 0)
	fragNormal = (vec4(inNormal, 0.0f) * uWorldTransform).xyz;

	// Pass along the texture coordinate to frag shader
	fragTexCoord = inTexCoord;
}
