#ifndef TRACK_BLOCK_H
#define TRACK_BLOCK_H

#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"
#include "Camera.h"
#include "..\Math\CollisionBox.h"
#include <math.h>

class TrackBlock
{
private:
	Model *modelBlock;
	Shader *shaderBlock;
	unsigned int sectorID;

public:
	TrackBlock();
	~TrackBlock();

	CollisionBox boundingBox;
	Vector3 position;
	Matrix4 rotate; 
	Vector3 scaleVec;
	enum BlockType
	{
		oscillation,
		stationary,
		rotating
	};
	BlockType blockType;
	bool moveToTarget;

	void Update(float deltaTime);
	void OscillationUpdate(float deltaTime);
	void RotatingUpdate(float deltaTime);
	void Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
};

#endif