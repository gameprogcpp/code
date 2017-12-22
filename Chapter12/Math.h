// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math
{
	const float Pi = 3.1415926535f;
	const float TwoPi = Pi * 2.0f;
	const float PiOver2 = Pi / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template <typename T>
	T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}

	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);
	}

	inline float Tan(float angle)
	{
		return tanf(angle);
	}

	inline float Acos(float value)
	{
		return acosf(value);
	}
	
	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}
	
	inline float Fmod(float numer, float denom)
	{
		return fmod(numer, denom);
	}
}

// 2D Vector
class Vector2
{
public:
	float x;
	float y;

	Vector2()
		:x(0.0f)
		,y(0.0f)
	{}

	explicit Vector2(float inX, float inY)
		:x(inX)
		,y(inY)
	{}

	// Set both components in one line
	void Set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

	// Vector addition (a + b)
	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	// Vector subtraction (a - b)
	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	// Component-wise multiplication
	// (a.x * b.x, ...)
	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	// Scalar multiplication
	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	// Scalar multiplication
	friend Vector2 operator*(float scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	// Scalar *=
	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	// Vector +=
	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	// Vector -=
	Vector2& operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	// Length squared of vector
	float LengthSq() const
	{
		return (x*x + y*y);
	}

	// Length of vector
	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// Normalize this vector
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	// Normalize the provided vector
	static Vector2 Normalize(const Vector2& vec)
	{
		Vector2 temp = vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static float Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x + a.y * b.y);
	}

	// Lerp from A to B by f
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
	{
		return Vector2(a + f * (b - a));
	}
	
	// Reflect V about (normalized) N
	static Vector2 Reflect(const Vector2& v, const Vector2& n)
	{
		return v - 2.0f * Vector2::Dot(v, n) * n;
	}

	// Transform vector by matrix
	static Vector2 Transform(const Vector2& vec, const class Matrix3& mat, float w = 1.0f);

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};

// 3D Vector
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
		:x(0.0f)
		,y(0.0f)
		,z(0.0f)
	{}

	explicit Vector3(float inX, float inY, float inZ)
		:x(inX)
		,y(inY)
		,z(inZ)
	{}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// Set all three components in one line
	void Set(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}

	// Vector addition (a + b)
	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	// Vector subtraction (a - b)
	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	// Component-wise multiplication
	friend Vector3 operator*(const Vector3& left, const Vector3& right)
	{
		return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	// Scalar multiplication
	friend Vector3 operator*(const Vector3& vec, float scalar)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	// Scalar multiplication
	friend Vector3 operator*(float scalar, const Vector3& vec)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	// Scalar *=
	Vector3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// Vector +=
	Vector3& operator+=(const Vector3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	// Vector -=
	Vector3& operator-=(const Vector3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	// Length squared of vector
	float LengthSq() const
	{
		return (x*x + y*y + z*z);
	}

	// Length of vector
	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// Normalize this vector
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	// Normalize the provided vector
	static Vector3 Normalize(const Vector3& vec)
	{
		Vector3 temp = vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static float Dot(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	// Cross product between two vectors (a cross b)
	static Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		Vector3 temp;
		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;
		return temp;
	}

	// Lerp from A to B by f
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
	{
		return Vector3(a + f * (b - a));
	}
	
	// Reflect V about (normalized) N
	static Vector3 Reflect(const Vector3& v, const Vector3& n)
	{
		return v - 2.0f * Vector3::Dot(v, n) * n;
	}

	static Vector3 Transform(const Vector3& vec, const class Matrix4& mat, float w = 1.0f);
	// This will transform the vector and renormalize the w component
	static Vector3 TransformWithPerspDiv(const Vector3& vec, const class Matrix4& mat, float w = 1.0f);

	// Transform a Vector3 by a quaternion
	static Vector3 Transform(const Vector3& v, const class Quaternion& q);

	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 NegUnitX;
	static const Vector3 NegUnitY;
	static const Vector3 NegUnitZ;
	static const Vector3 Infinity;
	static const Vector3 NegInfinity;
};

// 3x3 Matrix
class Matrix3
{
public:
	float mat[3][3];

	Matrix3()
	{
		*this = Matrix3::Identity;
	}

	explicit Matrix3(float inMat[3][3])
	{
		memcpy(mat, inMat, 9 * sizeof(float));
	}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}

	// Matrix multiplication
	friend Matrix3 operator*(const Matrix3& left, const Matrix3& right)
	{
		Matrix3 retVal;
		// row 0
		retVal.mat[0][0] = 
			left.mat[0][0] * right.mat[0][0] +
			left.mat[0][1] * right.mat[1][0] +
			left.mat[0][2] * right.mat[2][0];

		retVal.mat[0][1] = 
			left.mat[0][0] * right.mat[0][1] +
			left.mat[0][1] * right.mat[1][1] +
			left.mat[0][2] * right.mat[2][1];

		retVal.mat[0][2] = 
			left.mat[0][0] * right.mat[0][2] +
			left.mat[0][1] * right.mat[1][2] +
			left.mat[0][2] * right.mat[2][2];
		
		// row 1
		retVal.mat[1][0] = 
			left.mat[1][0] * right.mat[0][0] +
			left.mat[1][1] * right.mat[1][0] +
			left.mat[1][2] * right.mat[2][0];

		retVal.mat[1][1] = 
			left.mat[1][0] * right.mat[0][1] +
			left.mat[1][1] * right.mat[1][1] +
			left.mat[1][2] * right.mat[2][1];

		retVal.mat[1][2] = 
			left.mat[1][0] * right.mat[0][2] +
			left.mat[1][1] * right.mat[1][2] +
			left.mat[1][2] * right.mat[2][2];
		
		// row 2
		retVal.mat[2][0] = 
			left.mat[2][0] * right.mat[0][0] +
			left.mat[2][1] * right.mat[1][0] +
			left.mat[2][2] * right.mat[2][0];

		retVal.mat[2][1] =
			left.mat[2][0] * right.mat[0][1] +
			left.mat[2][1] * right.mat[1][1] +
			left.mat[2][2] * right.mat[2][1];

		retVal.mat[2][2] = 
			left.mat[2][0] * right.mat[0][2] +
			left.mat[2][1] * right.mat[1][2] +
			left.mat[2][2] * right.mat[2][2];

		return retVal;
	}

	Matrix3& operator*=(const Matrix3& right)
	{
		*this = *this * right;
		return *this;
	}

	// Create a scale matrix with x and y scales
	static Matrix3 CreateScale(float xScale, float yScale)
	{
		float temp[3][3] =
		{
			{ xScale, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}

	static Matrix3 CreateScale(const Vector2& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y);
	}

	// Create a scale matrix with a uniform factor
	static Matrix3 CreateScale(float scale)
	{
		return CreateScale(scale, scale);
	}

	// Create a rotation matrix about the Z axis
	// theta is in radians
	static Matrix3 CreateRotation(float theta)
	{
		float temp[3][3] =
		{
			{ Math::Cos(theta), Math::Sin(theta), 0.0f },
			{ -Math::Sin(theta), Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}

	// Create a translation matrix (on the xy-plane)
	static Matrix3 CreateTranslation(const Vector2& trans)
	{
		float temp[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ trans.x, trans.y, 1.0f },
		};
		return Matrix3(temp);
	}

	static const Matrix3 Identity;
};

// 4x4 Matrix
class Matrix4
{
public:
	float mat[4][4];

	Matrix4()
	{
		*this = Matrix4::Identity;
	}

	explicit Matrix4(float inMat[4][4])
	{
		memcpy(mat, inMat, 16 * sizeof(float));
	}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}

	// Matrix multiplication (a * b)
	friend Matrix4 operator*(const Matrix4& a, const Matrix4& b)
	{
		Matrix4 retVal;
		// row 0
		retVal.mat[0][0] = 
			a.mat[0][0] * b.mat[0][0] + 
			a.mat[0][1] * b.mat[1][0] + 
			a.mat[0][2] * b.mat[2][0] +
			a.mat[0][3] * b.mat[3][0];

		retVal.mat[0][1] = 
			a.mat[0][0] * b.mat[0][1] + 
			a.mat[0][1] * b.mat[1][1] + 
			a.mat[0][2] * b.mat[2][1] + 
			a.mat[0][3] * b.mat[3][1];

		retVal.mat[0][2] = 
			a.mat[0][0] * b.mat[0][2] + 
			a.mat[0][1] * b.mat[1][2] + 
			a.mat[0][2] * b.mat[2][2] + 
			a.mat[0][3] * b.mat[3][2];
		
		retVal.mat[0][3] = 
			a.mat[0][0] * b.mat[0][3] + 
			a.mat[0][1] * b.mat[1][3] + 
			a.mat[0][2] * b.mat[2][3] + 
			a.mat[0][3] * b.mat[3][3];

		// row 1
		retVal.mat[1][0] = 
			a.mat[1][0] * b.mat[0][0] + 
			a.mat[1][1] * b.mat[1][0] + 
			a.mat[1][2] * b.mat[2][0] + 
			a.mat[1][3] * b.mat[3][0];

		retVal.mat[1][1] = 
			a.mat[1][0] * b.mat[0][1] + 
			a.mat[1][1] * b.mat[1][1] + 
			a.mat[1][2] * b.mat[2][1] + 
			a.mat[1][3] * b.mat[3][1];

		retVal.mat[1][2] = 
			a.mat[1][0] * b.mat[0][2] + 
			a.mat[1][1] * b.mat[1][2] + 
			a.mat[1][2] * b.mat[2][2] + 
			a.mat[1][3] * b.mat[3][2];

		retVal.mat[1][3] = 
			a.mat[1][0] * b.mat[0][3] +
			a.mat[1][1] * b.mat[1][3] +
			a.mat[1][2] * b.mat[2][3] +
			a.mat[1][3] * b.mat[3][3];

		// row 2
		retVal.mat[2][0] = 
			a.mat[2][0] * b.mat[0][0] +
			a.mat[2][1] * b.mat[1][0] +
			a.mat[2][2] * b.mat[2][0] +
			a.mat[2][3] * b.mat[3][0];

		retVal.mat[2][1] = 
			a.mat[2][0] * b.mat[0][1] + 
			a.mat[2][1] * b.mat[1][1] + 
			a.mat[2][2] * b.mat[2][1] + 
			a.mat[2][3] * b.mat[3][1];

		retVal.mat[2][2] = 
			a.mat[2][0] * b.mat[0][2] +
			a.mat[2][1] * b.mat[1][2] + 
			a.mat[2][2] * b.mat[2][2] + 
			a.mat[2][3] * b.mat[3][2];

		retVal.mat[2][3] = 
			a.mat[2][0] * b.mat[0][3] + 
			a.mat[2][1] * b.mat[1][3] + 
			a.mat[2][2] * b.mat[2][3] + 
			a.mat[2][3] * b.mat[3][3];

		// row 3
		retVal.mat[3][0] = 
			a.mat[3][0] * b.mat[0][0] + 
			a.mat[3][1] * b.mat[1][0] + 
			a.mat[3][2] * b.mat[2][0] + 
			a.mat[3][3] * b.mat[3][0];

		retVal.mat[3][1] = 
			a.mat[3][0] * b.mat[0][1] + 
			a.mat[3][1] * b.mat[1][1] + 
			a.mat[3][2] * b.mat[2][1] + 
			a.mat[3][3] * b.mat[3][1];

		retVal.mat[3][2] = 
			a.mat[3][0] * b.mat[0][2] +
			a.mat[3][1] * b.mat[1][2] +
			a.mat[3][2] * b.mat[2][2] +
			a.mat[3][3] * b.mat[3][2];

		retVal.mat[3][3] = 
			a.mat[3][0] * b.mat[0][3] +
			a.mat[3][1] * b.mat[1][3] +
			a.mat[3][2] * b.mat[2][3] +
			a.mat[3][3] * b.mat[3][3];
		
		return retVal;
	}

	Matrix4& operator*=(const Matrix4& right)
	{
		*this = *this * right;
		return *this;
	}

	// Invert the matrix - super slow
	void Invert();

	// Get the translation component of the matrix
	Vector3 GetTranslation() const
	{
		return Vector3(mat[3][0], mat[3][1], mat[3][2]);
	}
	
	// Get the X axis of the matrix (forward)
	Vector3 GetXAxis() const
	{
		return Vector3::Normalize(Vector3(mat[0][0], mat[0][1], mat[0][2]));
	}

	// Get the Y axis of the matrix (left)
	Vector3 GetYAxis() const
	{
		return Vector3::Normalize(Vector3(mat[1][0], mat[1][1], mat[1][2]));
	}

	// Get the Z axis of the matrix (up)
	Vector3 GetZAxis() const
	{
		return Vector3::Normalize(Vector3(mat[2][0], mat[2][1], mat[2][2]));
	}

	// Extract the scale component from the matrix
	Vector3 GetScale() const
	{
		Vector3 retVal;
		retVal.x = Vector3(mat[0][0], mat[0][1], mat[0][2]).Length();
		retVal.y = Vector3(mat[1][0], mat[1][1], mat[1][2]).Length();
		retVal.z = Vector3(mat[2][0], mat[2][1], mat[2][2]).Length();
		return retVal;
	}

	// Create a scale matrix with x, y, and z scales
	static Matrix4 CreateScale(float xScale, float yScale, float zScale)
	{
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f, 0.0f },
			{ 0.0f, 0.0f, zScale, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateScale(const Vector3& scaleVector)
	{
		return CreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
	}

	// Create a scale matrix with a uniform factor
	static Matrix4 CreateScale(float scale)
	{
		return CreateScale(scale, scale, scale);
	}

	// Rotation about x-axis
	static Matrix4 CreateRotationX(float theta)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f , 0.0f },
			{ 0.0f, Math::Cos(theta), Math::Sin(theta), 0.0f },
			{ 0.0f, -Math::Sin(theta), Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Rotation about y-axis
	static Matrix4 CreateRotationY(float theta)
	{
		float temp[4][4] =
		{
			{ Math::Cos(theta), 0.0f, -Math::Sin(theta), 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ Math::Sin(theta), 0.0f, Math::Cos(theta), 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Rotation about z-axis
	static Matrix4 CreateRotationZ(float theta)
	{
		float temp[4][4] =
		{
			{ Math::Cos(theta), Math::Sin(theta), 0.0f, 0.0f },
			{ -Math::Sin(theta), Math::Cos(theta), 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Create a rotation matrix from a quaternion
	static Matrix4 CreateFromQuaternion(const class Quaternion& q);

	static Matrix4 CreateTranslation(const Vector3& trans)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 zaxis = Vector3::Normalize(target - eye);
		Vector3 xaxis = Vector3::Normalize(Vector3::Cross(up, zaxis));
		Vector3 yaxis = Vector3::Normalize(Vector3::Cross(zaxis, xaxis));
		Vector3 trans;
		trans.x = -Vector3::Dot(xaxis, eye);
		trans.y = -Vector3::Dot(yaxis, eye);
		trans.z = -Vector3::Dot(zaxis, eye);

		float temp[4][4] =
		{
			{ xaxis.x, yaxis.x, zaxis.x, 0.0f },
			{ xaxis.y, yaxis.y, zaxis.y, 0.0f },
			{ xaxis.z, yaxis.z, zaxis.z, 0.0f },
			{ trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateOrtho(float width, float height, float near, float far)
	{
		float temp[4][4] =
		{
			{ 2.0f / width, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 2.0f / height, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f / (far - near), 0.0f },
			{ 0.0f, 0.0f, near / (near - far), 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float near, float far)
	{
		float yScale = Math::Cot(fovY / 2.0f);
		float xScale = yScale * height / width;
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
			{ 0.0f, yScale, 0.0f, 0.0f },
			{ 0.0f, 0.0f, far / (far - near), 1.0f },
			{ 0.0f, 0.0f, -near * far / (far - near), 0.0f }
		};
		return Matrix4(temp);
	}

	// Create "Simple" View-Projection Matrix from Chapter 6
	static Matrix4 CreateSimpleViewProj(float width, float height)
	{
		float temp[4][4] =
		{
			{ 2.0f/width, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 2.0f/height, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f }
		};
		return Matrix4(temp);
	}
	
	static const Matrix4 Identity;
};

// (Unit) Quaternion
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		*this = Quaternion::Identity;
	}

	// This directly sets the quaternion components --
	// don't use for axis/angle
	explicit Quaternion(float inX, float inY, float inZ, float inW)
	{
		Set(inX, inY, inZ, inW);
	}

	// Construct the quaternion from an axis and angle
	// It is assumed that axis is already normalized,
	// and the angle is in radians
	explicit Quaternion(const Vector3& axis, float angle)
	{
		float scalar = Math::Sin(angle / 2.0f);
		x = axis.x * scalar;
		y = axis.y * scalar;
		z = axis.z * scalar;
		w = Math::Cos(angle / 2.0f);
	}

	// Directly set the internal components
	void Set(float inX, float inY, float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}

	void Conjugate()
	{
		x *= -1.0f;
		y *= -1.0f;
		z *= -1.0f;
	}

	float LengthSq() const
	{
		return (x*x + y*y + z*z + w*w);
	}

	float Length() const
	{
		return Math::Sqrt(LengthSq());
	}

	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	// Normalize the provided quaternion
	static Quaternion Normalize(const Quaternion& q)
	{
		Quaternion retVal = q;
		retVal.Normalize();
		return retVal;
	}

	// Linear interpolation
	static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f)
	{
		Quaternion retVal;
		retVal.x = Math::Lerp(a.x, b.x, f);
		retVal.y = Math::Lerp(a.y, b.y, f);
		retVal.z = Math::Lerp(a.z, b.z, f);
		retVal.w = Math::Lerp(a.w, b.w, f);
		retVal.Normalize();
		return retVal;
	}

	static float Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	// Spherical Linear Interpolation
	static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f)
	{
		float rawCosm = Quaternion::Dot(a, b);

		float cosom = -rawCosm;
		if (rawCosm >= 0.0f)
		{
			cosom = rawCosm;
		}

		float scale0, scale1;

		if (cosom < 0.9999f)
		{
			const float omega = Math::Acos(cosom);
			const float invSin = 1.f / Math::Sin(omega);
			scale0 = Math::Sin((1.f - f) * omega) * invSin;
			scale1 = Math::Sin(f * omega) * invSin;
		}
		else
		{
			// Use linear interpolation if the quaternions
			// are collinear
			scale0 = 1.0f - f;
			scale1 = f;
		}

		if (rawCosm < 0.0f)
		{
			scale1 = -scale1;
		}

		Quaternion retVal;
		retVal.x = scale0 * a.x + scale1 * b.x;
		retVal.y = scale0 * a.y + scale1 * b.y;
		retVal.z = scale0 * a.z + scale1 * b.z;
		retVal.w = scale0 * a.w + scale1 * b.w;
		retVal.Normalize();
		return retVal;
	}

	// Concatenate
	// Rotate by q FOLLOWED BY p
	static Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
	{
		Quaternion retVal;

		// Vector component is:
		// ps * qv + qs * pv + pv x qv
		Vector3 qv(q.x, q.y, q.z);
		Vector3 pv(p.x, p.y, p.z);
		Vector3 newVec = p.w * qv + q.w * pv + Vector3::Cross(pv, qv);
		retVal.x = newVec.x;
		retVal.y = newVec.y;
		retVal.z = newVec.z;

		// Scalar component is:
		// ps * qs - pv . qv
		retVal.w = p.w * q.w - Vector3::Dot(pv, qv);

		return retVal;
	}

	static const Quaternion Identity;
};

namespace Color
{
	static const Vector3 Black(0.0f, 0.0f, 0.0f);
	static const Vector3 White(1.0f, 1.0f, 1.0f);
	static const Vector3 Red(1.0f, 0.0f, 0.0f);
	static const Vector3 Green(0.0f, 1.0f, 0.0f);
	static const Vector3 Blue(0.0f, 0.0f, 1.0f);
	static const Vector3 Yellow(1.0f, 1.0f, 0.0f);
	static const Vector3 LightYellow(1.0f, 1.0f, 0.88f);
	static const Vector3 LightBlue(0.68f, 0.85f, 0.9f);
	static const Vector3 LightPink(1.0f, 0.71f, 0.76f);
	static const Vector3 LightGreen(0.56f, 0.93f, 0.56f);
}
