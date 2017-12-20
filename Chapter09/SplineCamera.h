// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "CameraComponent.h"
#include <vector>

struct Spline
{
	// Control points for spline
	// (Requires n+2 points where n is number
	// of points in segment)
	std::vector<Vector3> mControlPoints;
	// Given spline segment where startIdx = P1,
	// compute position based on t value
	Vector3 Compute(size_t startIdx, float t) const;
	// Returns number of control points
	size_t GetNumPoints() const { return mControlPoints.size(); }
};

class SplineCamera : public CameraComponent
{
public:
	SplineCamera(class Actor* owner);

	void Update(float deltaTime) override;
	// Restart the spline
	void Restart();

	void SetSpeed(float speed) { mSpeed = speed; }
	void SetSpline(const Spline& spline) { mPath = spline; }
	void SetPaused(bool pause) { mPaused = pause; }
private:
	// Spline path camera follows
	Spline mPath;
	// Current control point index and t
	size_t mIndex;
	float mT;
	// Amount t changes/sec
	float mSpeed;
	// Whether to move the camera long the path
	bool mPaused;
};
