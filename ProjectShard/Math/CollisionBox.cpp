#include "CollisionBox.h"

CollisionBox::CollisionBox(Vector3 c, Matrix4 &rotateMat, Vector3 e)
{
	boundingBox.c = c;
	boundingBox.u[0] = Vector3(rotateMat.data[0], rotateMat.data[1], rotateMat.data[2]);
	boundingBox.u[1] = Vector3(rotateMat.data[4], rotateMat.data[5], rotateMat.data[6]);
	boundingBox.u[2] = Vector3(rotateMat.data[8], rotateMat.data[9], rotateMat.data[10]);
	boundingBox.e = e;
}

CollisionBox::CollisionBox()
{
	boundingBox.c = Vector3();
	boundingBox.u[0] = Vector3();
	boundingBox.u[1] = Vector3();
	boundingBox.u[2] = Vector3();
	boundingBox.e = Vector3();
}

int CollisionBox::Intersects(CollisionBox &collisionBox)
{
	OBB a = this->boundingBox;
	OBB b = collisionBox.boundingBox;

	float ra, rb;
	Matrix33 R, AbsR;
	// Compute rotation matrix expressing b in a’s coordinate frame
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			R.data[i][j] = a.u[i].DotProduct(b.u[j]);

	// Check for identity rotation matrix in a's frame.
	//if(a.u[0] == Vector3(1.0f, 0.0f, 0.0f) && a.u[1] == Vector3(0.0f, 1.0f, 0.0f) && a.u[2] == Vector3(0.0f, 0.0f, 1.0f))
	{
		if (std::abs(a.c[0] - b.c[0]) >(a.e[0] + b.e[0])) return 0;
		if (std::abs(a.c[1] - b.c[1]) >(a.e[1] + b.e[1])) return 0;
		if (std::abs(a.c[2] - b.c[2]) > (a.e[2] + b.e[2])) return 0;
		return 1;
	}

	// Compute translation vector t
	Vector3 t = b.c - a.c;
	// Bring translation into a’s coordinate frame
	t = Vector3(t.DotProduct(a.u[0]), t.DotProduct(a.u[2]), t.DotProduct(a.u[2]));
	// Compute common subexpressions. Add in an epsilon term to
	// counteract arithmetic errors when two edges are parallel and
	// their cross product is (near) null (see text for details)
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			AbsR.data[i][j] = std::abs(R.data[i][j]);// +EPSILON;
	// Test axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; i++) {
		ra = a.e[i];
		rb = b.e[0] * AbsR.data[i][0] + b.e[1] * AbsR.data[i][1] + b.e[2] * AbsR.data[i][2];
		if (std::abs(t[i]) > ra + rb) return 0;
	}
	// Test axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; i++) {
		ra = a.e[0] * AbsR.data[0][i] + a.e[1] * AbsR.data[1][i] + a.e[2] * AbsR.data[2][i];
		rb = b.e[i];
		if (std::abs(t[0] * R.data[0][i] + t[1] * R.data[1][i] + t[2] * R.data[2][i]) > ra + rb) return 0;
	}
	// Test axis L = A0 x B0
	ra = a.e[1] * AbsR.data[2][0] + a.e[2] * AbsR.data[1][0];
	rb = b.e[1] * AbsR.data[0][2] + b.e[2] * AbsR.data[0][1];
	if (std::abs(t.data[2] * R.data[1][0] - t[1] * R.data[2][0]) > ra + rb) return 0;
	// Test axis L = A0 x B1
	ra = a.e[1] * AbsR.data[2][1] + a.e[2] * AbsR.data[1][1];
	rb = b.e[0] * AbsR.data[0][2] + b.e[2] * AbsR.data[0][0];
	if (std::abs(t[2] * R.data[1][1] - t[1] * R.data[2][1]) > ra + rb) return 0;
	// Test axis L = A0 x B2
	ra = a.e[1] * AbsR.data[2][2] + a.e[2] * AbsR.data[1][2];
	rb = b.e[0] * AbsR.data[0][1] + b.e[1] * AbsR.data[0][0];
	if (std::abs(t[2] * R.data[1][2] - t[1] * R.data[2][2]) > ra + rb) return 0;
	// Test axis L = A1 x B0
	ra = a.e[0] * AbsR.data[2][0] + a.e[2] * AbsR.data[0][0];
	rb = b.e[1] * AbsR.data[1][2] + b.e[2] * AbsR.data[1][1];

	if (std::abs(t[0] * R.data[2][0] - t[2] * R.data[0][0]) > ra + rb) return 0;
	// Test axis L = A1 x B1
	ra = a.e[0] * AbsR.data[2][1] + a.e[2] * AbsR.data[0][1];
	rb = b.e[0] * AbsR.data[1][2] + b.e[2] * AbsR.data[1][0];
	if (std::abs(t[0] * R.data[2][1] - t[2] * R.data[0][1]) > ra + rb) return 0;
	// Test axis L = A1 x B2
	ra = a.e[0] * AbsR.data[2][2] + a.e[2] * AbsR.data[0][2];
	rb = b.e[0] * AbsR.data[1][1] + b.e[1] * AbsR.data[1][0];
	if (std::abs(t[0] * R.data[2][2] - t[2] * R.data[0][2]) > ra + rb) return 0;
	// Test axis L = A2 x B0
	ra = a.e[0] * AbsR.data[1][0] + a.e[1] * AbsR.data[0][0];
	rb = b.e[1] * AbsR.data[2][2] + b.e[2] * AbsR.data[2][1];
	if (std::abs(t[1] * R.data[0][0] - t[0] * R.data[1][0]) > ra + rb) return 0;
	// Test axis L = A2 x B1
	ra = a.e[0] * AbsR.data[1][1] + a.e[1] * AbsR.data[0][1];
	rb = b.e[0] * AbsR.data[2][2] + b.e[2] * AbsR.data[2][0];
	if (std::abs(t[1] * R.data[0][1] - t[0] * R.data[1][1]) > ra + rb) return 0;
	// Test axis L = A2 x B2
	ra = a.e[0] * AbsR.data[1][2] + a.e[1] * AbsR.data[0][2];
	rb = b.e[0] * AbsR.data[2][1] + b.e[1] * AbsR.data[2][0];
	if (std::abs(t[1] * R.data[0][2] - t[0] * R.data[1][2]) > ra + rb) return 0;
	// Since no separating axis is found, the OBBs must be intersecting
	return 1;
}

void CollisionBox::UpdateBoundingBox(Vector3 c, Matrix4 &rotateMat, Vector3 e)
{
	boundingBox.c = c;
	boundingBox.u[0] = Vector3(rotateMat.data[0], rotateMat.data[1], rotateMat.data[2]);
	boundingBox.u[1] = Vector3(rotateMat.data[4], rotateMat.data[5], rotateMat.data[6]);
	boundingBox.u[2] = Vector3(rotateMat.data[8], rotateMat.data[9], rotateMat.data[10]);
	boundingBox.e = e;
}