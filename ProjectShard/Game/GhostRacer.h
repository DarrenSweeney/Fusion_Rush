#ifndef GHOST_RACER_H
#define GHOST_RACER_H

#include <sstream>
#include "..\Core\ResourceManager.h"
#include "Camera.h"
#include <istream>

class GhostRacer
{
public:
	GhostRacer();
	~GhostRacer();

	Vector3 position;
	float raceTime;

	void ReadRecordedPositions();
	void RestGhostRacer();
	void Update(float currentTrackTime);
	void Render(GLsizei screenWidth, GLsizei screenHeight, Camera &camera);

private:
	float lastTime;
	Model *ghostRacerModel;
	Shader *ghostRacerShader;
	Quaternion orientation;
	std::vector<Vector3> ghostRacerPositions;
	std::vector<Quaternion> ghostRacerOrientations;
	bool ghostRacerExists;
};

#endif