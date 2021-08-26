// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Math.h"
#include <rapidjson/document.h>
#include "Component.h"

class Actor
{
public:
	enum TypeID
	{
		TActor = 0,
		TBallActor,
		TFollowActor,
		TPlaneActor,
		TTargetActor,

		NUM_ACTOR_TYPES
	};

	static const char* TypeNames[NUM_ACTOR_TYPES];

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
	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const uint8_t* keyState);
	// Any actor-specific input code (overridable)
	virtual void ActorInput(const uint8_t* keyState);

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

	// Load/Save
	virtual void LoadProperties(const rapidjson::Value& inObj);
	virtual void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const;

	// Create an actor with specified properties
	template <typename T>
	static Actor* Create(class Game* game, const rapidjson::Value& inObj)
	{
		// Dynamically allocate actor of type T
		T* t = new T(game);
		// Call LoadProperties on new actor
		t->LoadProperties(inObj);
		return t;
	}

	// Search through component vector for one of type
	Component* GetComponentOfType(Component::TypeID type)
	{
		Component* comp = nullptr;
		for (Component* c : mComponents)
		{
			if (c->GetType() == type)
			{
				comp = c;
				break;
			}
		}
		return comp;
	}

	virtual TypeID GetType() const { return TActor; }

	const std::vector<Component*>& GetComponents() const { return mComponents; }
private:
	// Actor's state
	State mState;

	// Transform
	Matrix4 mWorldTransform;
	Vector3 mPosition;
	Quaternion mRotation;
	float mScale;
	bool mRecomputeTransform;

	std::vector<Component*> mComponents;
	class Game* mGame;
};
