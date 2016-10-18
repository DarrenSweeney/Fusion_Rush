#ifndef TRACK_BLOCK_H
#define TRACK_BLOCK_H

#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"
#include "Camera.h"
#include "..\Math\CollisionBox.h"

class TrackBlock
{
private:
	Model *modelBlock;
	Shader *shaderBlock;
	Matrix4 rotate;

public:
	TrackBlock();
	~TrackBlock();

	CollisionBox b1, b2;

	void Update();
	void Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	bool HitPlayer();
};

#endif