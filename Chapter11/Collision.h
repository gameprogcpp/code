// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Math.h"
#include <vector>

struct LineSegment
{
	LineSegment(const Vector3& start, const Vector3& end);
	// Get point along segment where 0 <= t <= 1
	Vector3 PointOnSegment(float t) const;
	// Get minimum distance squared between point and line segment
	float MinDistSq(const Vector3& point) const;
	// Get MinDistSq between two line segments
	static float MinDistSq(const LineSegment& s1, const LineSegment& s2);

	Vector3 mStart;
	Vector3 mEnd;
};

struct Plane
{
	Plane(const Vector3& normal, float d);
	// Construct plane from three points
	Plane(const Vector3& a, const Vector3& b, const Vector3& c);
	// Get the signed distance between the point and the plane
	float SignedDist(const Vector3& point) const;

	Vector3 mNormal;
	float mD;
};

struct Sphere
{
	Sphere(const Vector3& center, float radius);
	bool Contains(const Vector3& point) const;

	Vector3 mCenter;
	float mRadius;
};

struct AABB
{
	AABB(const Vector3& min, const Vector3& max);
	// Update min and max accounting for this point
	// (used when loading a model)
	void UpdateMinMax(const Vector3& point);
	// Rotated by a quaternion
	void Rotate(const Quaternion& q);
	bool Contains(const Vector3& point) const;
	float MinDistSq(const Vector3& point) const;

	Vector3 mMin;
	Vector3 mMax;
};

struct OBB
{
	Vector3 mCenter;
	Quaternion mRotation;
	Vector3 mExtents;
};

struct Capsule
{
	Capsule(const Vector3& start, const Vector3& end, float radius);
	// Get point along segment where 0 <= t <= 1
	Vector3 PointOnSegment(float t) const;
	bool Contains(const Vector3& point) const;

	LineSegment mSegment;
	float mRadius;
};

struct ConvexPolygon
{
	bool Contains(const Vector2& point) const;
	// Vertices have a clockwise ordering
	std::vector<Vector2> mVertices;
};

// Intersection functions
bool Intersect(const Sphere& a, const Sphere& b);
bool Intersect(const AABB& a, const AABB& b);
bool Intersect(const Capsule& a, const Capsule& b);
bool Intersect(const Sphere& s, const AABB& box);

bool Intersect(const LineSegment& l, const Sphere& s, float& outT);
bool Intersect(const LineSegment& l, const Plane& p, float& outT);
bool Intersect(const LineSegment& l, const AABB& b, float& outT,
	Vector3& outNorm);

bool SweptSphere(const Sphere& P0, const Sphere& P1,
	const Sphere& Q0, const Sphere& Q1, float& t);
