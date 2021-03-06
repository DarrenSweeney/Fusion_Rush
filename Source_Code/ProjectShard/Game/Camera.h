#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include "..\Math\Vector3.h"
#include "..\Math\matrix4x4.h"
#include "..\Math\MathHelper.h"
#include <GL/gl3w.h>
#include "..\Input\InputManager.h"

using namespace std;

/*
	This Camera does not allow pich value higher than 90 degress.
	Will be good enough for a simple camera to attach to the player.
*/
class Camera
{
public:
	Camera(Vector3 &position, Vector3 &worldUp = Vector3(0.0f, 1.0f, 0.0f), GLfloat yaw = -90.0f,
		GLfloat pitch = -5.0f, GLfloat speed = 2.0f, GLfloat sensitivity = 0.1f, GLfloat zoom = 45.0f);

	// Returns the view martrix calculated using Euler Angles and the LookAt matrix
	Matrix4 &GetViewMatrix();
	// Returns the projection matrix of the camera
	Matrix4 &GetProjectionMatrix(GLsizei screenWidth, GLsizei screenHeight);

	void SetPosition(Vector3 &pos);
	Vector3 GetPosition();
	void Roll(GLfloat angle);

	void KeyboardMovement(GLfloat deltaTime);
	void MouseMovement(GLfloat xOffset, GLfloat yOffset);

private:
	Vector3 frontVec;
	Vector3 upVec;
	Vector3 rightVec;
	Vector3 worldUp;
	GLfloat yaw;
	GLfloat pitch;
	GLfloat mouseSensitivity;
	Vector3 position;
	Matrix4 view;
	GLfloat cameraSpeed, movementSpeed;
	GLfloat zoom;

	void UpdateCameraVectors();
};

#endif