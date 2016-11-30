#ifndef PLAYER_H
#define PLAYER_H

#include "..\Renderer\Model.h"
#include "..\Renderer\Shader.h"
#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"
#include "..\Math\Quaternion.h"
#include "..\Input\InputManager.h"
#include "Camera.h"
#include "..\Math\CollisionBox.h"
#include "..\Renderer\DebugDrawManager.h"

class Player
{
public:
	Player();
	~Player();

	void Update(float deltaTime);
	void Spawn();
	void Render(GLsizei screenWidth, GLsizei screenHeight);
	void Reflection(GLsizei screenWidth, GLsizei screenHeight);
	float GetSpeed();

	Camera camera;
	CollisionBox boundingBox;
	Vector3 linearVelocity;
	float speed;
	Vector3 position;
	bool updateMovement;

private:
	Model *model;
	Shader *shaderModel;
	Vector3 acceleration;
	Quaternion orientation;
	float rotationSpeed;
	Matrix4 modelRotate;
	const float JOYSTICK_DEAD_ZONE = 0.2f;

	void Movement(float deltaTime);
};

#endif