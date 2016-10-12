#ifndef TRACK_H
#define TRACK_H

#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"
#include "..\Math\Vector4.h"
#include "Camera.h"

class Track
{
public:
	Track();
	~Track();
	void Init();
	void SetUpBuffers(GLuint &vao, Matrix4 *matrices);
	void Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);

private:
	Model *raceTrack;
	Shader *instancingShader;
	GLuint amount;
	Matrix4 *modelMatrices;
	GLuint buffer;
};

#endif