#include "Buildings.h"

Buildings::Buildings()
{
	amount = 100;
	refleModelMatrices = new Matrix4[amount];
	modelMatrices = new Matrix4[amount];

	buildingModel = g_resourceMgr.GetModel(SID("Building"));
	reflecBuildingModel = g_resourceMgr.GetModel(SID("BuildingReflection"));

	UseInstancingShader();
	glUniform3f(glGetUniformLocation(ShaderProgramID(), "skyColour"), 0.8f, 0.45f, 0.4f);

	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(20.0f, 20.0f, 20.0f));
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int buildingXPos = i % 2 == 0 ? 90.0f : -90.0f;
		transMatrix = transMatrix.translate(Vector3(buildingXPos, -25.0f, -80.0f * i));
		modelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < buildingModel->meshes.size(); i++)
		SetUpBuffers(buildingModel->meshes[i].VAO, modelMatrices, amount);

	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(19.9f, 19.9f, 19.9f));
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int buildingXPos = i % 2 == 0 ? 90.0f : -90.0f;
		transMatrix = transMatrix.translate(Vector3(buildingXPos, -100.0f, -80.0f * i));
		refleModelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < reflecBuildingModel->meshes.size(); i++)
		SetUpBuffers(reflecBuildingModel->meshes[i].VAO, refleModelMatrices, amount);
}

Buildings::~Buildings()
{
	delete buildingModel;
	delete reflecBuildingModel;
	delete[] modelMatrices;
	delete[] refleModelMatrices;
}

void Buildings::Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();

	UseInstancingShader();
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "view"), 1, GL_FALSE, &view.data[0]);

	RenderInstance(buildingModel, amount);
}

void Buildings::RenderReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();

	UseInstancingShader();
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "view"), 1, GL_FALSE, &view.data[0]);

	RenderInstance(reflecBuildingModel, amount);
}