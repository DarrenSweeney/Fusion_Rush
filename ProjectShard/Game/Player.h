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
#include <sstream>

class Player
{
public:
	Player();
	~Player();

	void Update(float deltaTime);
	void FinishedAnimation(float delatTime);
	void Spawn();
	void Render(GLsizei screenWidth, GLsizei screenHeight);
	void Reflection(GLsizei screenWidth, GLsizei screenHeight);
	float GetSpeed();
	void WriteRecordedPositions();

	Camera camera;
	CollisionBox boundingBox;
	Vector3 linearVelocity;
	float speed;
	Vector3 position;
	bool recordRace;
	bool updateMovement;
	bool shipDestroyed;

private:
	Model *model;
	Shader *shaderModel;
	Vector3 acceleration;
	Vector3 oldPosition;
	Quaternion orientation;
	float rotationSpeed;
	Matrix4 modelRotate;
	const float JOYSTICK_DEAD_ZONE = 0.05f;
	float cameraInterpolator, interpolator;
	float currentTimePos;
	float lastTime;
	float currentTrackTime;
	std::vector<Vector3> recordPositions;
	std::vector<Quaternion> recordOrientation;

	void Movement(float deltaTime);
	void RecordPosition();
	void PlayExplodeAnimation();
};
#endif