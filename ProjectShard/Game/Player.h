#ifndef PLAYER_H
#define PLAYER_H

#include "..\Renderer\Model.h"
#include "..\Renderer\Shader.h"
#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"
#include "..\Math\Quaternion.h"
#include "Camera.h"
#include "..\Input\InputManager.h"

class Player
{
public:
	Player();
	~Player();

	void Update(float deltaTime);
	void Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);

private:
	Model *model;
	Shader *shaderModel;
	Vector3 position;
	Vector3 linearVelocity;	
	Quaternion orientation;
	float rotationSpeed;
};

#endif