// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Math.h"
class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);
	// Any actor-specific input code (overridable)
	virtual void ProcessInput(const uint8_t* keys) { }

	// Getters/setters
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeTransform = true; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeTransform = true; }
	const Quaternion& GetRotation() const { return mRotation; }
	void SetRotation(const Quaternion& rotation) { mRotation = rotation;   mRecomputeTransform = true; }
	
	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }

	void RotateToNewForward(const Vector3& forward);

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	// Actor's state
	State mState;

	// Transform
	Matrix4 mWorldTransform;
	Vector3 mPosition;
	Quaternion mRotation;
	float mScale;
	bool mRecomputeTransform;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};
