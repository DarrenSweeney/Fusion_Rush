#include "TrackSections.h"

TrackSections::TrackSections()
{
	amount = 80;
	modelMatrices = new Matrix4[amount];

	trackModel = g_resourceMgr.GetModel(SID("RaceTrack"));
	UseInstancingShader();
	glUniform3f(glGetUniformLocation(ShaderProgramID(), "skyColour"), 0.0f, 0.0f, 0.0f);

	Matrix4 scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(3.0f, 0.0f, 3.0f));
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 transMatrix = Matrix4();

		transMatrix = transMatrix.translate(Vector3(0.0f, -4.0f, (-120.0f * i)));
		modelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < trackModel->meshes.size(); i++)
		SetUpBuffers(trackModel->meshes[i].VAO, modelMatrices, amount);
}

TrackSections::~TrackSections()
{
	delete trackModel;
	delete[] modelMatrices;
}

void TrackSections::Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();

	UseInstancingShader();
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "view"), 1, GL_FALSE, &view.data[0]);

	RenderInstance(trackModel, amount);
}