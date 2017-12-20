// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SplineCamera.h"
#include "Actor.h"

Vector3 Spline::Compute(size_t startIdx, float t) const
{
	// Check if startIdx is out of bounds
	if (startIdx >= mControlPoints.size())
	{
		return mControlPoints.back();
	}
	else if (startIdx == 0)
	{
		return mControlPoints[startIdx];
	}
	else if (startIdx + 2 >= mControlPoints.size())
	{
		return mControlPoints[startIdx];
	}

	// Get p0 through p3
	Vector3 p0 = mControlPoints[startIdx - 1];
	Vector3 p1 = mControlPoints[startIdx];
	Vector3 p2 = mControlPoints[startIdx + 1];
	Vector3 p3 = mControlPoints[startIdx + 2];
	// Compute position according to Catmull-Rom equation
	Vector3 position = 0.5f * ((2.0f * p1) + (-1.0f * p0 + p2) * t +
		(2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t +
		(-1.0f * p0 + 3.0f * p1 - 3.0f * p2 + p3) * t * t * t);
	return position;
}

SplineCamera::SplineCamera(Actor* owner)
	:CameraComponent(owner)
	,mIndex(1)
	,mT(0.0f)
	,mSpeed(0.5f)
	,mPaused(true)
{
}

void SplineCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	// Update t value
	if (!mPaused)
	{
		mT += mSpeed * deltaTime;
		// Advance to the next control point if needed.
		// This assumes speed isn't so fast that you jump past
		// multiple control points in one frame.
		if (mT >= 1.0f)
		{
			// Make sure we have enough points to advance the path
			if (mIndex < mPath.GetNumPoints() - 3)
			{
				mIndex++;
				mT = mT - 1.0f;
			}
			else
			{
				// Path's done, so pause
				mPaused = true;
			}
		}
	}

	// Camera position is the spline at the current t/index
	Vector3 cameraPos = mPath.Compute(mIndex, mT);
	// Target point is just a small delta ahead on the spline
	Vector3 target = mPath.Compute(mIndex, mT + 0.01f);
	// Assume spline doesn't flip upside-down
	const Vector3 up = Vector3::UnitZ;
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}

void SplineCamera::Restart()
{
	mIndex = 1;
	mT = 0.0f;
	mPaused = false;
}
