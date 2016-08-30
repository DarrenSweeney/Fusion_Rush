#include "Vector3.h"

Vector3::Vector3()
	: x(0), y(0), z(0)
{

}

Vector3::Vector3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{

}

float Vector3::operator[](int x)
{
	assert(x >= 0 && x < 3);

	return data[x];
}

Vector3 Vector3::operator+(Vector3 &vec3)
{
	return Vector3(x + vec3.x, y + vec3.y, z + vec3.z);
}

Vector3 &Vector3::operator+=(Vector3 &vec3)
{
	x += vec3.x;
	y += vec3.y;
	z += vec3.z;

	return *this;
}

Vector3 Vector3::operator-(Vector3 &vec3)
{
	return Vector3(x - vec3.x, y - vec3.y, z - vec3.z);
}

Vector3 &Vector3::operator-=(Vector3 &vec3)
{
	x -= vec3.x;
	y -= vec3.y;
	z -= vec3.z;

	return *this;
}

Vector3 Vector3::operator*(Vector3 &vec3)
{
	return Vector3(x * vec3.x, y * vec3.y, z * vec3.z);
}

Vector3 Vector3::operator*(float value)
{
	return Vector3(x * value, y * value, z * value);
}

Vector3 &Vector3::operator*=(Vector3 &vec3)
{
	x *= vec3.x;
	y *= vec3.y;
	z *= vec3.z;

	return *this;
}

Vector3 &Vector3::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

float Vector3::DotProduct(Vector3 &vec3)
{
	return x * vec3.x + y * vec3.y + z * vec3.z;
}

Vector3 Vector3::VectorProduct(Vector3 &vec3)
{
	return Vector3(y*vec3.z - z*vec3.y, z*vec3.x - x*vec3.z, x*vec3.y - y*vec3.x);
}

Vector3 Vector3::CrossProduct(Vector3 &vec3_One, Vector3 &vec3_Two)
{
	return Vector3(vec3_Two.y*vec3_One.z - vec3_Two.z*vec3_One.y, vec3_Two.z*vec3_One.x
		- vec3_Two.x*vec3_One.z, vec3_Two.x*vec3_One.y - vec3_Two.y*vec3_One.x);
}

void Vector3::MakeOrthinormalBasis(Vector3 &a, Vector3 &b, Vector3 &c)
{
	a.normalise();
	c = a.VectorProduct(b);

	if (c.SquareMagnitude() == 0.0f)
		return;

	c.normalise();
	b = c.VectorProduct(a);
}

void Vector3::clear()
{
	x, y, z = 0;
}

void Vector3::Invert()
{
	x *= -1;
	y *= -1;
	z *= -1;
}

float Vector3::Magnitude()
{
	return sqrtf(x*x + y*y + z*z);
}

float Vector3::SquareMagnitude()
{
	return (x*x + y*y + z*z);
}

Vector3 Vector3::normalise()
{
	if (Magnitude() > 0)
	{
		*this *= 1 / Magnitude();
	}

	return *this;
}