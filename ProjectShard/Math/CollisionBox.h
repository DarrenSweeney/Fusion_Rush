#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "Vector3.h"
#include <cmath>

struct OBB
{
	Vector3 c;		// OBB center point
	Vector3 u[3];	// Local x-, y-, and z-axes
	Vector3 e;		// Positive halfwidth extents of OBB along each axis
};

struct Matrix33
{
	float data[3][3];
};

class CollisionBox
{
public:
	CollisionBox();

	int TestOBBOBB(OBB &a, OBB &b);
};

#endif