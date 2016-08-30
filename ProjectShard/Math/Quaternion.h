#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"
#include <assert.h>

class Quaternion
{
public:
	union
	{
		struct { float w, x, y, z; };

		float data[4];
	};

	Quaternion();
	Quaternion(float _w, float _x, float _y, float _z);

	Quaternion operator*(const Quaternion &quaternion) const;
	Quaternion &operator*=(const Quaternion &quaternion);

	void Identity();
	void Normalize();
	Quaternion Conjugate();
	
	Quaternion RotateX(float angle);
	Quaternion RotateY(float angle);
	Quaternion RotateZ(float angle);
	Quaternion RotateAboutAxis(const Vector3 axis, float angle);
};

#endif