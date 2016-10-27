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
	// TODO(Darren): What to only have one skycolor in the track class
	Vector3 skyColour;
	// Collision boxes for the barriers on the track
	CollisionBox leftB_BoundingBox, rightB_BoundingBox;
	TrackBlock debug_block;

	Buildings buildings;
	Barriers barriers;
	TrackSections trackSections;

public:
	RacingTrack();
	~RacingTrack();

	void Init();
	void Update(float deltaTime);
	bool TrackCollision(CollisionBox &playerBoundingBox);
	void RenderSceneObjects(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderTrack(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderTrackReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
};

#endif