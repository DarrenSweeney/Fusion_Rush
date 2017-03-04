#ifndef RACING_TRACK_H
#define RACING_TRACK_H

#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"
#include "..\Math\Vector4.h"
#include "Camera.h"
#include "Buildings.h"
#include "Barriers.h"
#include "TrackSections.h"
#include "TrackBlock.h"
#include <stdlib.h>
#include <time.h>

class RacingTrack
{
private:
	unsigned int blockAmount;
	TrackBlock *trackBlock;

	Buildings buildings;
	Barriers barriers;
	TrackSections trackSections;
	Model *finishModel;
	Shader *modelShader;

public:
	RacingTrack();
	~RacingTrack();

	Vector3 startRacePosition, finishRacePosition;

	void Init(int raceTrackSeed);
	void Update(float deltaTime);
	bool ObstacleCollision(CollisionBox &playerBoundingBox);
	bool BarrierCollision(CollisionBox &playerBoundingBox, Vector3 &playerPosition);
	void RenderSceneObjects(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderTrack(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderTrackReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
};

#endif