#include "Buildings.h"

Buildings::Buildings()
{
	amount = 130;
	building_1.refleModelMatrices = new Matrix4[amount];
	building_1.modelMatrices = new Matrix4[amount];

	building_1.buildingModel = g_resourceMgr.GetModel(SID("Building"));
	building_1.reflecBuildingModel = g_resourceMgr.GetModel(SID("BuildingReflection"));

	building_2.refleModelMatrices = new Matrix4[amount];
	building_2.modelMatrices = new Matrix4[amount];

	building_2.buildingModel = g_resourceMgr.GetModel(SID("Building_2"));
	building_2.reflecBuildingModel = g_resourceMgr.GetModel(SID("BuildingReflection_2"));

	UseInstancingShader();
	glUniform3f(glGetUniformLocation(ShaderProgramID(), "skyColour"), 0.0f, 0.0f, 0.0f);

	Matrix4 scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(20.0f, 20.0f, 20.0f));
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int buildingXPos = i % 2 == 0 ? 90.0f : -90.0f;
		transMatrix = transMatrix.translate(Vector3(buildingXPos, -25.0f, -80.0f * i));
		building_1.modelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < building_1.buildingModel->meshes.size(); i++)
		SetUpBuffers(building_1.buildingModel->meshes[i].VAO, building_1.modelMatrices, amount);

	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(19.9f, 19.9f, 19.9f));
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int buildingXPos = i % 2 == 0 ? 90.0f : -90.0f;
		transMatrix = transMatrix.translate(Vector3(buildingXPos, -100.0f, -80.0f * i));
		building_1.refleModelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < building_1.reflecBuildingModel->meshes.size(); i++)
		SetUpBuffers(building_1.reflecBuildingModel->meshes[i].VAO, building_1.refleModelMatrices, amount);

	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(20.0f, 20.0f, 20.0f));
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int buildingXPos = i % 2 == 0 ? 100.0f : -100.0f;
		transMatrix = transMatrix.translate(Vector3(buildingXPos, -25.0f, (-80.0f * i) + 70.0f));
		building_2.modelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < building_2.buildingModel->meshes.size(); i++)
		SetUpBuffers(building_2.buildingModel->meshes[i].VAO, building_2.modelMatrices, amount);

	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(19.9f, 19.9f, 19.9f));
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int buildingXPos = i % 2 == 0 ? 100.0f : -100.0f;
		transMatrix = transMatrix.translate(Vector3(buildingXPos, -100.0f, (-80.0f * i) + 70.0f));
		building_2.refleModelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < building_2.reflecBuildingModel->meshes.size(); i++)
		SetUpBuffers(building_2.reflecBuildingModel->meshes[i].VAO, building_2.refleModelMatrices, amount);
}

Buildings::~Buildings()
{
	DeleteBuilding(building_1);
	DeleteBuilding(building_2);
}

void Buildings::Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();

	UseInstancingShader();
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "view"), 1, GL_FALSE, &view.data[0]);

	RenderInstance(building_1.buildingModel, amount);
	RenderInstance(building_2.buildingModel, amount);
}

void Buildings::RenderReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();

	UseInstancingShader();
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "view"), 1, GL_FALSE, &view.data[0]);

	RenderInstance(building_1.reflecBuildingModel, amount);
	RenderInstance(building_2.reflecBuildingModel, amount);
}

void Buildings::CreateBuilding(BuildingData building, const char* modelName, const char* modelReflName)
{
	building.refleModelMatrices = new Matrix4[amount];
	building.modelMatrices = new Matrix4[amount];

	building.buildingModel = g_resourceMgr.GetModel(SID(modelName));
	building.reflecBuildingModel = g_resourceMgr.GetModel(SID(modelReflName));
}

void Buildings::DeleteBuilding(BuildingData building)
{
	delete building.buildingModel;
	delete building.reflecBuildingModel;
	delete[] building.modelMatrices;
	delete[] building.refleModelMatrices;
}