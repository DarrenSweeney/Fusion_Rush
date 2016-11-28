#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "..\Renderer\InstancingEntity.h"
#include "..\Renderer\Model.h"
#include "Camera.h"

class Buildings : public InstancingEntity
{
public:
	Buildings();
	~Buildings();
	void Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);
	void RenderReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);

private:
	Model *buildingModel, *reflecBuildingModel;
	Matrix4 *modelMatrices, *refleModelMatrices;
};

#endif