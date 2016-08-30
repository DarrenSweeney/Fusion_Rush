#include "Quaternion.h"

Quaternion::Quaternion()
{
	w = 1;
	x, y, z = 0;
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z)
	: w(_w), x(_x), y(_y), z(_z)
{

}

void Quaternion::Identity()
{
	w = 1;
	x, y, z = 0;
}

Quaternion Quaternion::operator*(const Quaternion &multiplier) const
{
	Quaternion result;

	result.w = w*multiplier.w - x*multiplier.x - y*multiplier.y - z*multiplier.z;
	result.x = w*multiplier.x + x*multiplier.w + z*multiplier.y - y*multiplier.z;
	result.y = w*multiplier.y + y*multiplier.w + x*multiplier.z - z*multiplier.x;
	result.z = w*multiplier.z + z*multiplier.w + y*multiplier.x - x*multiplier.y;

	return result;
}

Quaternion &Quaternion::operator*=(const Quaternion &multiplier)
{
	Quaternion q = *this;

	w = q.w*multiplier.w - q.x*multiplier.x - q.y*multiplier.y - q.z*multiplier.z;
	x = q.w*multiplier.x + q.x*multiplier.w + q.y*multiplier.z - q.z*multiplier.y;
	y = q.w*multiplier.y + q.y*multiplier.w + q.z*multiplier.x - q.x*multiplier.z;
	z = q.w*multiplier.z + q.z*multiplier.w + q.x*multiplier.y - q.y*multiplier.x;

	return *this;
}

void Quaternion::Normalize()
{
	// Compute magnitude of the quaternion
	float mag = (float)sqrt(w*w + x*x + y*y + z*z);

	// Avoid divide by zero
	if (mag > 0.0f) 
	{
		// Normalize it
		float oneOverMag = 1.0f / mag;
		w *= oneOverMag;
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
	else 
	{
		assert(false);
		Identity();
	}
}

Quaternion Quaternion::Conjugate()
{
	x *= -1;
	y *= -1;
	z *= -1;

	return *this;
}

Quaternion Quaternion::RotateX(float angle)
{
	// Computer half angle
	float angleOver2 = angle * 0.5f;

	w = cos(angleOver2);
	x = sin(angleOver2);
	y = 0.0f;
	z = 0.0f;

	return *this;
}

Quaternion Quaternion::RotateY(float angle)
{
	// Computer half angle
	float angleOver2 = angle * 0.5f;

	w = cos(angleOver2);
	x = 0.0f;
	y = sin(angleOver2);
	z = 0.0f;

	return *this;
}

Quaternion Quaternion::RotateZ(float angle)
{
	// Computer half angle
	float angleOver2 = angle * 0.5f;

	w = cos(angleOver2);
	x = 0.0f;
	y = 0.0f;
	z = sin(angleOver2);

	return *this;
}

Quaternion Quaternion::RotateAboutAxis(Vector3 axis, float angle)
{
	// The axis of rotation must be normalized
	assert(fabs(axis.Magnitude() - 1.0f) < 0.01f);

	// Compute the half angle and its sin
	float angleOver2 = angle * 0.5f;
	float sinAngleOver2 = sin(angleOver2);

	w = cos(sinAngleOver2);
	x = axis.x * sinAngleOver2;
	y = axis.y * sinAngleOver2;
	z = axis.z * sinAngleOver2;

	return *this;
}