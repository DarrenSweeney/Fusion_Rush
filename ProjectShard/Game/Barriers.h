#ifndef BARRIERS_H
#define BARRIERS_H

#include "..\Renderer\InstancingEntity.h"
#include "..\Renderer\Model.h"
#include "Camera.h"

class Barriers : public InstancingEntity
{
public:
	Barriers();
	~Barriers();
	void Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);

private:
	Model *barrierModel, *reflecBarrierModel;
	Matrix4 *modelMatrices, *refleModelMatrices;
	Matrix4 scaleMatrix;
};

#endif