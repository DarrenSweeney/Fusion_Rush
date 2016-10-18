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
	CollisionBox b1, b2;

public:
	TrackBlock();
	~TrackBlock();
	
	void Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	bool HitPlayer();
};

#endif