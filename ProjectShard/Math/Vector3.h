#ifndef Vector3_H
#define Vector3_H

#include <math.h>
#include <assert.h>

class Vector3
{
public:
	union
	{
		struct { float x, y, z; };

		float data[3];
	};

public:
	Vector3();
	Vector3(float x, float y, float z);

	float operator[](int x);
	Vector3 operator+(Vector3 &vec3);
	Vector3 &operator+=(Vector3 &vec3);
	Vector3 operator-(Vector3 &vec3);
	Vector3 &operator-=(Vector3 &vec3);
	Vector3 operator*(Vector3 &vec3);
	Vector3 operator*(float value);
	Vector3 &operator*=(Vector3 &vec3);
	Vector3 &operator*=(float value);

	float DotProduct(Vector3 &vec3);
	Vector3 VectorProduct(Vector3 &vec3);
	Vector3 CrossProduct(Vector3 &vec3_one, Vector3 &vec3_two);

	void MakeOrthinormalBasis(Vector3 &a, Vector3 &b, Vector3 &c);

	void clear();
	void Invert();
	float Magnitude();
	float SquareMagnitude();
	Vector3 normalise();
};

#endif
