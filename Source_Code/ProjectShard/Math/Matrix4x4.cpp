#include "Matrix4x4.h"

Matrix4::Matrix4()
{
	data[1] = data[2] = data[3] = data[4] = data[6] =
		data[7] = data[8] = data[9] = data[11] =
		data[12] = data[13] = data[14] = 0.0f;
	data[0] = data[5] = data[10] = data[15] = 1.0f;
}

Matrix4::Matrix4(float m11, float m12, float m13, float m14,
	float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34,
	float m41, float m42, float m43, float m44)
{
	data[0] = m11; data[1] = m12; data[2] = m13; data[3] = m14;
	data[4] = m21; data[5] = m22; data[6] = m23; data[7] = m24;
	data[8] = m31; data[9] = m32; data[10] = m33; data[11] = m34;
	data[12] = m41; data[13] = m42; data[14] = m43; data[15] = m44;
}

Matrix4 &Matrix4::operator+=(float value)
{
	data[0] += value;	data[1] += value;	data[2] += value;	data[3] += value;
	data[4] += value;	data[5] += value;	data[6] += value;	data[7] += value;
	data[8] += value;	data[9] += value;	data[10] += value;	data[11] += value;
	data[12] += value;	data[13] += value;	data[14] += value;	data[15] += value;

	return *this;
}

Matrix4 &Matrix4::operator-=(float value)
{
	data[0] -= value;	data[1] -= value;	data[2] -= value;	data[3] -= value;
	data[4] -= value;	data[5] -= value;	data[6] -= value;	data[7] -= value;
	data[8] -= value;	data[9] -= value;	data[10] -= value;	data[11] -= value;
	data[12] -= value;	data[13] -= value;	data[14] -= value;	data[15] -= value;

	return *this;
}

Matrix4 &Matrix4::operator*=(float value)
{
	data[0] *= value;	data[1] *= value;	data[2] *= value;	data[3] *= value;
	data[4] *= value;	data[5] *= value;	data[6] *= value;	data[7] *= value;
	data[8] *= value;	data[9] *= value;	data[10] *= value;	data[11] *= value;
	data[12] *= value;	data[9] *= value;	data[10] *= value;	data[11] *= value;

	return *this;
}

Vector4 Matrix4::operator*(Vector4 &vec4)
{
	Vector4 result = Vector4();

	result.x = data[0] * vec4.x + data[1] * vec4.y + data[2] * vec4.z + data[3] * vec4.w;
	result.y = data[4] * vec4.x + data[5] * vec4.y + data[6] * vec4.z + data[7] * vec4.w;
	result.z = data[8] * vec4.x + data[9] * vec4.y + data[10] * vec4.z + data[11] * vec4.w;
	result.w = data[12] * vec4.x + data[13] * vec4.y + data[14] * vec4.z + data[15] * vec4.w;

	return result;
}

Matrix4 &Matrix4::operator*=(Matrix4 &matrix)
{
	data[0] = data[0] * matrix.data[0] + data[1] * matrix.data[4] + data[2] * matrix.data[8] + data[3] * matrix.data[12];
	data[1] = data[0] * matrix.data[1] + data[1] * matrix.data[5] + data[2] * matrix.data[9] + data[3] * matrix.data[13];
	data[2] = data[0] * matrix.data[2] + data[1] * matrix.data[6] + data[2] * matrix.data[10] + data[3] * matrix.data[14];
	data[3] = data[0] * matrix.data[3] + data[1] * matrix.data[7] + data[2] * matrix.data[11] + data[3] * matrix.data[15];

	data[4] = data[4] * matrix.data[0] + data[5] * matrix.data[4] + data[6] * matrix.data[8] + data[7] * matrix.data[12];
	data[5] = data[4] * matrix.data[1] + data[5] * matrix.data[5] + data[6] * matrix.data[9] + data[7] * matrix.data[13];
	data[6] = data[4] * matrix.data[2] + data[5] * matrix.data[6] + data[6] * matrix.data[10] + data[7] * matrix.data[14];
	data[7] = data[4] * matrix.data[3] + data[5] * matrix.data[7] + data[6] * matrix.data[11] + data[7] * matrix.data[15];

	data[8] = data[8] * matrix.data[0] + data[9] * matrix.data[4] + data[10] * matrix.data[8] + data[11] * matrix.data[12];
	data[9] = data[8] * matrix.data[1] + data[9] * matrix.data[5] + data[10] * matrix.data[9] + data[11] * matrix.data[13];
	data[10] = data[8] * matrix.data[2] + data[9] * matrix.data[6] + data[10] * matrix.data[10] + data[11] * matrix.data[14];
	data[11] = data[8] * matrix.data[3] + data[9] * matrix.data[7] + data[10] * matrix.data[11] + data[11] * matrix.data[15];

	data[12] = data[12] * matrix.data[0] + data[13] * matrix.data[4] + data[14] * matrix.data[8] + data[15] * matrix.data[12];
	data[13] = data[12] * matrix.data[1] + data[13] * matrix.data[5] + data[14] * matrix.data[9] + data[15] * matrix.data[13];
	data[14] = data[12] * matrix.data[2] + data[13] * matrix.data[6] + data[14] * matrix.data[10] + data[15] * matrix.data[14];
	data[15] = data[12] * matrix.data[3] + data[13] * matrix.data[7] + data[14] * matrix.data[11] + data[15] * matrix.data[15];

	return *this;
}

Matrix4 operator*(Matrix4 &matrixA, Matrix4 &matrixB)
{
	Matrix4 matrixAnswer;

	matrixAnswer.data[0] = (matrixA.data[0] * matrixB.data[0]) + (matrixA.data[1] * matrixB.data[4]) + (matrixA.data[2] * matrixB.data[8]) + (matrixA.data[3] * matrixB.data[12]);
	matrixAnswer.data[1] = (matrixA.data[0] * matrixB.data[1]) + (matrixA.data[1] * matrixB.data[5]) + (matrixA.data[2] * matrixB.data[9]) + (matrixA.data[3] * matrixB.data[13]);
	matrixAnswer.data[2] = (matrixA.data[0] * matrixB.data[2]) + (matrixA.data[1] * matrixB.data[6]) + (matrixA.data[2] * matrixB.data[10]) + (matrixA.data[3] * matrixB.data[14]);
	matrixAnswer.data[3] = (matrixA.data[0] * matrixB.data[3]) + (matrixA.data[1] * matrixB.data[7]) + (matrixA.data[2] * matrixB.data[11]) + (matrixA.data[3] * matrixB.data[15]);

	matrixAnswer.data[4] = (matrixA.data[4] * matrixB.data[0]) + (matrixA.data[5] * matrixB.data[4]) + (matrixA.data[6] * matrixB.data[8]) + (matrixA.data[7] * matrixB.data[12]);
	matrixAnswer.data[5] = matrixA.data[4] * matrixB.data[1] + matrixA.data[5] * matrixB.data[5] + matrixA.data[6] * matrixB.data[9] + matrixA.data[7] * matrixB.data[13];
	matrixAnswer.data[6] = matrixA.data[4] * matrixB.data[2] + matrixA.data[5] * matrixB.data[6] + matrixA.data[6] * matrixB.data[10] + matrixA.data[7] * matrixB.data[14];
	matrixAnswer.data[7] = matrixA.data[4] * matrixB.data[3] + matrixA.data[5] * matrixB.data[7] + matrixA.data[6] * matrixB.data[11] + matrixA.data[7] * matrixB.data[15];

	matrixAnswer.data[8] = matrixA.data[8] * matrixB.data[0] + matrixA.data[9] * matrixB.data[4] + matrixA.data[10] * matrixB.data[8] + matrixA.data[11] * matrixB.data[12];
	matrixAnswer.data[9] = matrixA.data[8] * matrixB.data[1] + matrixA.data[9] * matrixB.data[5] + matrixA.data[10] * matrixB.data[9] + matrixA.data[11] * matrixB.data[13];
	matrixAnswer.data[10] = matrixA.data[8] * matrixB.data[2] + matrixA.data[9] * matrixB.data[6] + matrixA.data[10] * matrixB.data[10] + matrixA.data[11] * matrixB.data[14];
	matrixAnswer.data[11] = matrixA.data[8] * matrixB.data[3] + matrixA.data[9] * matrixB.data[7] + matrixA.data[10] * matrixB.data[11] + matrixA.data[11] * matrixB.data[15];

	matrixAnswer.data[12] = matrixA.data[12] * matrixB.data[0] + matrixA.data[13] * matrixB.data[4] + matrixA.data[14] * matrixB.data[8] + matrixA.data[15] * matrixB.data[12];
	matrixAnswer.data[13] = matrixA.data[12] * matrixB.data[1] + matrixA.data[13] * matrixB.data[5] + matrixA.data[14] * matrixB.data[9] + matrixA.data[15] * matrixB.data[13];
	matrixAnswer.data[14] = matrixA.data[12] * matrixB.data[2] + matrixA.data[13] * matrixB.data[6] + matrixA.data[14] * matrixB.data[10] + matrixA.data[15] * matrixB.data[14];
	matrixAnswer.data[15] = matrixA.data[12] * matrixB.data[3] + matrixA.data[13] * matrixB.data[7] + matrixA.data[14] * matrixB.data[11] + matrixA.data[15] * matrixB.data[15];

	return matrixAnswer;
}

Matrix4 Matrix4::operator=(Matrix4 & matrix)
{
	data[0] = matrix.data[0];
	data[1] = matrix.data[1];
	data[2] = matrix.data[2];
	data[3] = matrix.data[3];

	data[4] = matrix.data[4];
	data[5] = matrix.data[5];
	data[6] = matrix.data[6];
	data[7] = matrix.data[7];

	data[8] = matrix.data[8];
	data[9] = matrix.data[9];
	data[10] = matrix.data[10];
	data[11] = matrix.data[11];

	data[12] = matrix.data[12];
	data[13] = matrix.data[13];
	data[14] = matrix.data[14];
	data[15] = matrix.data[15];

	return *this;
}

Matrix4 &Matrix4::scale(Vector3 &scale)
{
	*this = Matrix4();

	data[0] *= scale.x;
	data[5] *= scale.y;
	data[10] *= scale.z;

	return *this;
}

Matrix4 &Matrix4::translate(Vector3 &vec3)
{
	*this = Matrix4();

	data[12] += vec3.x;
	data[13] += vec3.y;
	data[14] += vec3.z;

	return *this;
}

// Anti - clockwise rotation around a arbitrary axis.
// Where x^2 + y^2 + z^2 = 1;
Matrix4 Matrix4::rotate(float angle, Vector3 &vec3)
{
	*this = Matrix4();

	// Normalize vector
	vec3.normalise();

	data[0] = cos(angle) + (vec3.x * vec3.x) * (1 - cos(angle));
	data[1] = (vec3.x * vec3.y) * (1 - cos(angle)) + (vec3.z * sin(angle));
	data[2] = (vec3.x * vec3.z) * (1 - cos(angle)) - (vec3.y * sin(angle));

	data[4] = (vec3.x * vec3.y) * (1 - cos(angle)) - (vec3.z * sin(angle));
	data[5] = cos(angle) + (vec3.y * vec3.y) * (1 - cos(angle));
	data[6] = (vec3.y * vec3.z) * (1 - cos(angle)) + (vec3.x * sin(angle));

	data[8] = (vec3.x * vec3.z) * (1 - cos(angle)) + (vec3.y * sin(angle));
	data[9] = (vec3.y * vec3.z) * (1 - cos(angle)) - (vec3.x * sin(angle));
	data[10] = cos(angle) + (vec3.z * vec3.z) * (1 - cos(angle));

	return *this;
}

// Anti-clockwise rotation around the x axis.
Matrix4 Matrix4::rotateX(float angle)
{
	*this = Matrix4();

	data[5] = cos(angle);
	data[6] = sin(angle);
	data[9] = -sin(angle);
	data[10] = cos(angle);

	return *this;
}

// Anti-clockwise rotation around the y axis.
Matrix4 Matrix4::rotateY(float angle)
{
	*this = Matrix4();

	data[0] = cos(angle);
	data[2] = -sin(angle);
	data[8] = sin(angle);
	data[10] = cos(angle);

	return *this;
}

// Anti-clockwise rotation around the z axis.
Matrix4 Matrix4::rotateZ(float angle)
{
	*this = Matrix4();

	data[0] = cos(angle);
	data[1] = sin(angle);
	data[4] = -sin(angle);
	data[5] = cos(angle);

	return *this;
}

Matrix4 Matrix4::setFrustrum(float l, float w, float b, float t, float n, float f)
{
	data[0] = (2 * n) / (w - l);
	data[5] = (2 * n) / (t - b);
	data[8] = (w + l) / (w - l);
	data[9] = (t + b) / (t - b);
	data[10] = -((f + n) / (f - n));
	data[11] = -1;
	data[14] = -((2 * n * f) / (f - n));
	data[15] = 0;

	return *this;
}

Matrix4 Matrix4::perspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	float tangent = tanf((fov * 0.5) * (PI / 180));
	float height = nearPlane * tangent;
	float width = height * aspectRatio;

	setFrustrum(-width, width, -height, height, nearPlane, farPlane);

	return *this;
}

Matrix4 Matrix4::orthographicProjection(float left, float right, float bottom, float top, float near, float far)
{
	data[0] = 2 / (right - left);
	data[5] = 2 / (top - bottom);
	data[10] = -2 / (far - near);
	data[12] = -(right + left) / (right - left);
	data[13] = -(top + bottom) / (top - bottom);
	data[14] = -(far + near) / (far - near);
	data[15] = 1;	// Set to one incase we do perspective then othrographic for some reason.

	return *this;
}

//							Eye,			Center,				Up
Matrix4 Matrix4::lookAt(Vector3 &position, Vector3 &target, Vector3 &worldUp)
{
	// Camera Direction.
	Vector3 zAxis = (position - target).normalise();
	// Positive right axis vector
	Vector3 xAxis = (worldUp.VectorProduct(zAxis)).normalise();
	// Camera up vector.
	Vector3 yAxis = zAxis.VectorProduct(xAxis);

	data[0] = xAxis.x;
	data[1] = yAxis.x;
	data[2] = zAxis.x;

	data[4] = xAxis.y;
	data[5] = yAxis.y;
	data[6] = zAxis.y;

	data[8] = xAxis.z;
	data[9] = yAxis.z;
	data[10] = zAxis.z;

	data[12] = -(xAxis.DotProduct(position));
	data[13] = -(yAxis.DotProduct(position));
	data[14] = -(zAxis.DotProduct(position));

	return *this;
}

Matrix4 Matrix4::transpose(Matrix4 &matrix)
{
	data[0] = matrix.data[0];
	data[1] = matrix.data[4];
	data[2] = matrix.data[8];
	data[3] = matrix.data[12];

	data[4] = matrix.data[1];
	data[5] = matrix.data[5];
	data[6] = matrix.data[9];
	data[7] = matrix.data[13];

	data[8] = matrix.data[2];
	data[9] = matrix.data[6];
	data[10] = matrix.data[10];
	data[11] = matrix.data[14];

	data[12] = matrix.data[3];
	data[13] = matrix.data[7];
	data[14] = matrix.data[11];
	data[15] = matrix.data[15];

	return *this;
}

Matrix4 Matrix4::QuaternionToMatrix4(const Quaternion &q)
{
	float ww = 2.0f * q.w;
	float xx = 2.0f * q.x;
	float yy = 2.0f * q.y;
	float zz = 2.0f * q.z;

	data[0] = 1.0f - yy*q.y - zz*q.z;
	data[1] = xx*q.y + ww*q.z;
	data[2] = xx*q.z - ww*q.y;
	data[4] = xx*q.y - ww*q.z;
	data[5] = 1.0f - xx*q.x - zz*q.z;
	data[6] = yy*q.z + ww*q.x;
	data[8] = xx*q.z + ww*q.y;
	data[9] = yy*q.z - ww*q.x;
	data[10] = 1.0f - xx*q.x - yy*q.y;

	return *this;
}