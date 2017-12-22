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

// This corresponds to the output color to the color buffer
layout(location = 0) out vec4 outColor;

// Different textures from G-buffer
uniform sampler2D uGDiffuse;
uniform sampler2D uGNormal;
uniform sampler2D uGWorldPos;

// Create a struct for the point light
struct PointLight
{
	// Position of light
	vec3 mWorldPos;
	// Diffuse color
	vec3 mDiffuseColor;
	// Radius of the light
	float mInnerRadius;
	float mOuterRadius;
};

uniform PointLight uPointLight;
// Stores width/height of screen
uniform vec2 uScreenDimensions;

void main()
{
	// From this fragment, calculate the coordinate to sample into the G-buffer
	vec2 gbufferCoord = gl_FragCoord.xy / uScreenDimensions;
	
	// Sample from G-buffer
	vec3 gbufferDiffuse = texture(uGDiffuse, gbufferCoord).xyz;
	vec3 gbufferNorm = texture(uGNormal, gbufferCoord).xyz;
	vec3 gbufferWorldPos = texture(uGWorldPos, gbufferCoord).xyz;
	
	// Surface normal
	vec3 N = normalize(gbufferNorm);
	// Vector from surface to light
	vec3 L = normalize(uPointLight.mWorldPos - gbufferWorldPos);

	// Compute Phong diffuse component for the light
	vec3 Phong = vec3(0.0, 0.0, 0.0);
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		// Get the distance between the light and the world pos
		float dist = distance(uPointLight.mWorldPos, gbufferWorldPos);
		// Use smoothstep to compute value in range [0,1]
		// between inner/outer radius
		float intensity = smoothstep(uPointLight.mInnerRadius,
									 uPointLight.mOuterRadius, dist);
		// The diffuse color of the light depends on intensity
		vec3 DiffuseColor = mix(uPointLight.mDiffuseColor,
								vec3(0.0, 0.0, 0.0), intensity);
		Phong = DiffuseColor * NdotL;
	}

	// Final color is texture color times phong light (alpha = 1)
	outColor = vec4(gbufferDiffuse * Phong, 1.0);
}
