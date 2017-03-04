#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "Vector3.h"
#include "Matrix4x4.h"
#include <cmath>

class CollisionBox
{
private:
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

public:
	CollisionBox(Vector3 c, Matrix4 &rotateMat, Vector3 e);
	CollisionBox();
	OBB boundingBox;

	int Intersects(CollisionBox &collisionBox);
	void UpdateBoundingBox(Vector3 c, Matrix4 &rotateMat, Vector3 e);
};

#endif