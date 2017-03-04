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
	struct BuildingData
	{
		Model *buildingModel, *reflecBuildingModel;
		Matrix4 *modelMatrices, *refleModelMatrices;
	};

	BuildingData building_1;
	BuildingData building_2;

	void CreateBuilding(BuildingData building, const char* modelName, const char* modelReflName);
	void DeleteBuilding(BuildingData building);
};

#endif