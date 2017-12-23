// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Component.h"
#include "Actor.h"
#include "LevelLoader.h"

const char* Component::TypeNames[NUM_COMPONENT_TYPES] = {
	"Component",
	"AudioComponent",
	"BallMove",
	"BoxComponent",
	"CameraComponent",
	"FollowCamera",
	"MeshComponent",
	"MoveComponent",
	"SkeletalMeshComponent",
	"SpriteComponent",
	"MirrorCamera",
	"PointLightComponent",
	"TargetComponent"
};

Component::Component(Actor* owner, int updateOrder)
	:mOwner(owner)
	,mUpdateOrder(updateOrder)
{
	// Add to actor's vector of components
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}

void Component::OnUpdateWorldTransform()
{
}

void Component::LoadProperties(const rapidjson::Value& inObj)
{
	JsonHelper::GetInt(inObj, "updateOrder", mUpdateOrder);
}

void Component::SaveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	JsonHelper::AddInt(alloc, inObj, "updateOrder", mUpdateOrder);
}
