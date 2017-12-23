// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Collision.h"

class BoxComponent : public Component
{
public:
	BoxComponent(class Actor* owner, int updateOrder = 100);
	~BoxComponent();

	void OnUpdateWorldTransform() override;

	void SetObjectBox(const AABB& model) { mObjectBox = model; }
	const AABB& GetWorldBox() const { return mWorldBox; }

	TypeID GetType() const override { return TBoxComponent; }

	void LoadProperties(const rapidjson::Value& inObj) override;
	void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const override;
	void SetShouldRotate(bool value) { mShouldRotate = value; }
private:
	AABB mObjectBox;
	AABB mWorldBox;
	bool mShouldRotate;
};
