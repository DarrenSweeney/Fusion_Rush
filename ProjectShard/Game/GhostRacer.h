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

	void ReadRecordedPositions();
	void Update();
	void Render(GLsizei screenWidth, GLsizei screenHeight, Camera &camera);

private:
	GLfloat lastTime;
	Model *ghostRacerModel;
	Shader *ghostRacerShader;
	Vector3 position;
	Quaternion orientation;
	std::vector<Vector3> ghostRacerPositions;
};

#endif