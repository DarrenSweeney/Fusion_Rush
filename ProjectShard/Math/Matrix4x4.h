#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "MathHelper.h"
#include "Vector3.h"
#include "Vector4.h"

// This is a column-major 4x4 matrix.
class Matrix4
{
public:
	float data[16];

	Matrix4();
	Matrix4(int m11, int m12, int m13, int m14,
		int m21, int m22, int m23, int m24,
		int m31, int m32, int m33, int m34,
		int m41, int m42, int m43, int m44);

	Vector4 operator*(Vector4 &vec4);
	Matrix4 &operator+=(float value);
	Matrix4 &operator-=(float value);
	Matrix4 &operator*=(float value);
	Matrix4 &operator*=(Matrix4 &matrix);
	Matrix4 operator=(Matrix4 &matrix);

	Matrix4 &scale(Vector3 &vec3);
	Matrix4 &translate(Vector3 &vec3);

	// TODO(Darren): What if x have anxis to rotate but x change it because of the refernece.
	Matrix4 rotate(float angle, Vector3 &vec3);
	Matrix4 rotateX(float angle);
	Matrix4 rotateY(float angle);
	Matrix4 rotateZ(float angle);

	Matrix4 setFrustrum(float l, float w, float b, float t, float n, float f);
	Matrix4 perspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
	Matrix4 orthographicProjection(float left, float right, float bottom, float top, float near, float far);
	Matrix4 lookAt(Vector3 &position, Vector3 &target, Vector3 &worldUp);
	Matrix4 transpose(Matrix4 &matrix);
};

Matrix4 operator*(Matrix4 &matrixA, Matrix4 &matrixB);

#endif