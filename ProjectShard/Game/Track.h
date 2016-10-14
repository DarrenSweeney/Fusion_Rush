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
	void RenderSceneObjects(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderTrack(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderTrackReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);

private:
	Model *raceTrack;
	Model *trackBarrier, *reflecTrackBarrier;
	Model *building, *reflecBuilding;
	Shader *instancingShader;
	GLuint trackAmount, barrierAmount, buildingAmount;
	Matrix4 *trackModelMatrices;
	Matrix4 *barrierModelMatrices, *barrierRefleMatrices;
	Matrix4 *buildingModelMatrices, *buildingRefleMatrices;

	void SetUpBuffers(GLuint &vao, Matrix4 *matrices, GLuint amount);
	void RenderInstance(Model *model, GLuint amount);
};

#endif