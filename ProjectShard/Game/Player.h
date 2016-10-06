#ifndef PLAYER_H
#define PLAYER_H

#include "..\Renderer\Model.h"
#include "..\Renderer\Shader.h"
#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"
#include "..\Math\Quaternion.h"
#include "..\Input\InputManager.h"
#include "Camera.h"

class Player
{
public:
	Player();
	~Player();

	void Update(float deltaTime);
	void Render(GLsizei screenWidth, GLsizei screenHeight);

	// TODO(Darren): Take this out.
	Camera camera;

private:
	Model *model;
	Shader *shaderModel;
	Vector3 position;
	Vector3 linearVelocity;	
	Quaternion orientation;
	float rotationSpeed;
};

#endif