#include "Buildings.h"

Buildings::Buildings()
{
	amount = 100;
	modelMatrices = new Matrix4[amount];

	buildingModel = g_resourceMgr.GetModel(SID("Building"));
	UseInstancingShader();
	glUniform3f(glGetUniformLocation(ShaderProgramID(), "skyColour"), 0.5f, 0.5f, 0.5f);
}

void Buildings::Init()
{
	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(19.9f, 19.9f, 19.9f));
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int buildingXPos = i % 2 == 0 ? 90.0f : -90.0f;
		transMatrix = transMatrix.translate(Vector3(buildingXPos, -100.0f, -80.0f * i));
		modelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < buildingModel->meshes.size(); i++)
		SetUpBuffers(buildingModel->meshes[i].VAO, modelMatrices, amount);
}

Buildings::~Buildings()
{
	delete buildingModel;
	delete reflecBuildingModel;
	delete[] modelMatrices;
}

void Buildings::Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{

}

void Buildings::RenderReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view;
	view = camera.GetViewMatrix();

	UseInstancingShader();
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "view"), 1, GL_FALSE, &view.data[0]);

	RenderInstance(buildingModel, amount);
}