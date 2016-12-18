#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "MathHelper.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"

class Matrix4
{
public:
	float data[16];

	Matrix4();
	Matrix4(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	Vector4 operator*(Vector4 &vec4);
	Matrix4 &operator+=(float value);
	Matrix4 &operator-=(float value);
	Matrix4 &operator*=(float value);
	Matrix4 &operator*=(Matrix4 &matrix);
	Matrix4 operator=(Matrix4 &matrix);

	Matrix4 &scale(Vector3 &vec3);
	Matrix4 &translate(Vector3 &vec3);

	Matrix4 rotate(float angle, Vector3 &vec3);
	Matrix4 rotateX(float angle);
	Matrix4 rotateY(float angle);
	Matrix4 rotateZ(float angle);

	Matrix4 setFrustrum(float l, float w, float b, float t, float n, float f);
	Matrix4 perspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
	Matrix4 orthographicProjection(float left, float right, float bottom, float top, float near, float far);
	Matrix4 lookAt(Vector3 &position, Vector3 &target, Vector3 &worldUp);
	Matrix4 transpose(Matrix4 &matrix);
	Matrix4 QuaternionToMatrix4(const Quaternion &q);
};

Matrix4 operator*(Matrix4 &matrixA, Matrix4 &matrixB);

#endif