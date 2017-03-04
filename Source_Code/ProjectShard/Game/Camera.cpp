#include "camera.h"

Camera::Camera(Vector3 &_position, Vector3 &worldUp, GLfloat _yaw, GLfloat _pitch, GLfloat speed, GLfloat sensitivity, GLfloat zoom)
	: movementSpeed(speed), mouseSensitivity(sensitivity), zoom(zoom), cameraSpeed(60.0f)
{
	position = _position;
	upVec = worldUp;
	yaw = _yaw;
	pitch = _pitch;
	frontVec = Vector3(0.0f, 0.0f, -1.0f);
	UpdateCameraVectors();
	movementSpeed = 15.0f;
}

Matrix4 &Camera::GetViewMatrix()
{
	return view.lookAt(position, position + frontVec, upVec);
}

Matrix4 &Camera::GetProjectionMatrix(GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = Matrix4();

	return projection.perspectiveProjection(zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 20000.0f);
}

void Camera::SetPosition(Vector3 &pos)
{
	position = pos;
}

Vector3 Camera::GetPosition()
{
	return position;
}

void Camera::KeyboardMovement(GLfloat deltaTime)
{
	bool moving = false;

	GLfloat velocity = (movementSpeed * 1.0f) * deltaTime;
	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_W))
	{
		position += (frontVec * velocity);
		moving = true;
	}
	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_S))
	{
		position -= (frontVec * velocity);
		moving = true;
	}
	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_A))
	{
		position -= (frontVec.VectorProduct(upVec).normalise() * velocity);
		moving = true;
	}
	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_D))
	{
		position += (frontVec.VectorProduct(upVec).normalise() * velocity);
		moving = true;
	}

	UpdateCameraVectors();
}

void Camera::MouseMovement(GLfloat xOffset, GLfloat yOffset)
{
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	UpdateCameraVectors();
}

void Camera::Roll(GLfloat angle)
{
	rightVec = (rightVec * cos(MathHelper::DegressToRadians(angle)) +
		upVec * sin(MathHelper::DegressToRadians(angle))).normalise();

	upVec = frontVec.VectorProduct(rightVec).normalise();

	upVec *= -1;
}

void Camera::UpdateCameraVectors()
{
	Vector3 frontVec;
	frontVec.x = cos(MathHelper::DegressToRadians(yaw)) * cos(MathHelper::DegressToRadians(pitch));
	frontVec.y = sin(MathHelper::DegressToRadians(pitch));
	frontVec.z = sin(MathHelper::DegressToRadians(yaw)) * cos(MathHelper::DegressToRadians(pitch));
	frontVec.normalise();

	this->frontVec = frontVec;
}