#pragma once
#include <sstream>
#include <math.h>

struct Vector3
{
	float x;
	float y;
	float z;
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	
	const Vector3 operator+(const Vector3& other) const
	{
		return Vector3(x+other.x, y+other.y, z+other.z);
	}
	const Vector3 operator-() const
	{
		return Vector3(-x, -y, -z);
	}
	const Vector3 operator-(const Vector3& other) const
	{
		return Vector3(x-other.x, y-other.y, z-other.z);
	}
	friend Vector3 operator*(const Vector3& v, const float scalar)
	{
		return Vector3(v.x*scalar, v.y*scalar, v.z*scalar);
	}
	friend Vector3 operator*(const float scalar, const Vector3& v)
	{
		return Vector3(v.x*scalar, v.y*scalar, v.z*scalar);
	}
	friend Vector3 operator/(const Vector3& v, const float scalar)
	{
		return Vector3(v.x/scalar, v.y/scalar, v.z/scalar);
	}
	float DotProduct(const Vector3& other) const
	{
		return x*other.x + y*other.y + z*other.z;
	}
	Vector3 CrossProduct(const Vector3& other) const
	{
		return Vector3(
			y * other.z - z * other.y,
			x * other.z - z * other.x,
			x * other.y - y * other.x);
	}
	float Length() const
	{
		return sqrt(x*x+y*y+z*z);
	}
	const Vector3 Normal() const
	{
		auto length = Length();
		return Vector3(x/length, y/length, z/length);
	}

	std::string ToString() const
	{
		std::ostringstream result;
		// Special c++ madness to avoid -0 in the output!
		// https://stackoverflow.com/a/12536877
		result << "(" << (x==0?0:x) << ", " << (y==0?0:y) << ", " << (z==0?0:z) << ")";
		return result.str();
	}
};
