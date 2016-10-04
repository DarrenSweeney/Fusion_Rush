#include "Quaternion.h"

Quaternion::Quaternion()
{
	w = 1;
	x = 0;
	y = 0;
	z = 0;
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

float Quaternion::Dot(const Quaternion q0, const Quaternion q1)
{
	float result = q0.w * q1.w + q0.x * q1.x + q0.y * q1.y + q0.z * q1.z;

	return result;
}

Quaternion Quaternion::Slerp(const Quaternion &q0, const Quaternion &q1, float t)
{
	// Check for out-of range parameter and return edge points if so
	if (t <= 0.0f) return q0;
	if (t >= 1.0f) return q1;
	// Compute "cosine of angle between quaternions" using dot product
		float cosOmega = Dot(q0, q1);
	// If negative dot, use –q1. Two quaternions q and –q
	// represent the same rotation, but may produce
	// different slerp. We chose q or –q to rotate using
	// the acute angle.
	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;
	if (cosOmega < 0.0f) {
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmega = -cosOmega;
	}
	// We should have two unit quaternions, so dot should be <= 1.0
	assert(cosOmega < 1.1f);
	// Compute interpolation fraction, checking for quaternions
	// almost exactly the same
	float k0, k1;
	if (cosOmega > 0.9999f) {
		// Very close - just use linear interpolation,
		// which will protect againt a divide by zero
		k0 = 1.0f-t;
		k1 = t;
	}
	else {
		// Compute the sin of the angle using the
		// trig identity sin^2(omega) + cos^2(omega) = 1
		float sinOmega = sqrt(1.0f - cosOmega*cosOmega);
		// Compute the angle from its sin and cosine
		float omega = atan2(sinOmega, cosOmega);
		// Compute inverse of denominator, so we only have
		// to divide once
		float oneOverSinOmega = 1.0f / sinOmega;
		// Compute interpolation parameters
		k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
		k1 = sin(t * omega) * oneOverSinOmega;
	}

	Quaternion result;
	result.x = k0*q0.x + k1*q1x;
	result.y = k0*q0.y + k1*q1y;
	result.z = k0*q0.z + k1*q1z;
	result.w = k0*q0.w + k1*q1w;
	// Return it
	return result;
}