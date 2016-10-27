#ifndef TRACK_H
#define TRACK_H

#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"
#include "..\Math\Vector4.h"
#include "Camera.h"
#include "TrackBlock.h"
#include <stdlib.h>
#include <time.h>

class Track
{
private:
	Model *raceTrack;
	Model *trackBarrier, *reflecTrackBarrier;
	Model *building, *reflecBuilding;
	Shader *instancingShader;
	GLuint trackAmount, barrierAmount, buildingAmount;
	Matrix4 *trackModelMatrices;
	Matrix4 *barrierModelMatrices, *barrierRefleMatrices;
	Matrix4 *buildingModelMatrices, *buildingRefleMatrices;
	unsigned int blockAmount;
	TrackBlock *trackBlock;
	Vector3 skyColour;
	// Collision boxes for the barriers on the track
	CollisionBox leftB_BoundingBox, rightB_BoundingBox;
	TrackBlock debug_block;

	void SetUpBuffers(GLuint &vao, Matrix4 *matrices, GLuint amount);
	void RenderInstance(Model *model, GLuint amount);

public:
	Track();
	~Track();
	void Init();
	void Update(float deltaTime);
	bool TrackCollision(CollisionBox &playerBoundingBox);
	void RenderSceneObjects(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderTrack(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderTrackReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
};

#endif