#include "Barriers.h"

Barriers::Barriers()
{
	amount = 200;
	modelMatrices = new Matrix4[amount];
	refleModelMatrices = new Matrix4[amount];

	barrierModel = g_resourceMgr.GetModel(SID("Barrier"));
	reflecBarrierModel = g_resourceMgr.GetModel(SID("BarrierReflection"));
	UseInstancingShader();
	glUniform3f(glGetUniformLocation(ShaderProgramID(), "skyColour"), 0.5f, 0.5f, 0.5f);

	scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(3.0f, 5.0f, 3.0f));
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int rotateDeg = i % 2 == 0 ? 0.0f : -180.0f;
		rotate = rotate.rotateY(MathHelper::DegressToRadians(rotateDeg));

		int barrierZPos = i;
		if (barrierZPos % 2 == 0)
			barrierZPos = (-60.0f) * i;
		else if (barrierZPos % 2 == 1)
			barrierZPos = (-60.0f) * (i - 1);

		int barrierXPos = i % 2 == 0 ? 60.0f : -60.0f;
		transMatrix = transMatrix.translate(Vector3(barrierXPos, 1.0f, barrierZPos));
		modelMatrices[i] = scaleMatrix * rotate * transMatrix;
	}

	for (GLuint i = 0; i < barrierModel->meshes.size(); i++)
		SetUpBuffers(barrierModel->meshes[i].VAO, modelMatrices, amount);

	scaleMatrix = Matrix4();
	Vector3 scaleVec(3.0f, 5.0f, 3.0f);
	scaleMatrix = scaleMatrix.scale(scaleVec);
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 transMatrix = Matrix4();
		Matrix4 rotate = Matrix4();

		int rotateDeg = i % 2 == 0 ? 0.0f : -180.0f;
		rotate = rotate.rotateY(MathHelper::DegressToRadians(rotateDeg));

		int barrierZPos = i;
		if (barrierZPos % 2 == 0)
			barrierZPos = -60.0f * i;
		else if (barrierZPos % 2 == 1)
			barrierZPos = -60.0f * (i - 1);

		int barrierXPos = i % 2 == 0 ? 60.0f : -60.0f;
		transMatrix = transMatrix.translate(Vector3(barrierXPos, -9.0f, barrierZPos));
		refleModelMatrices[i] = scaleMatrix * rotate * transMatrix;
	}

	for (GLuint i = 0; i < reflecBarrierModel->meshes.size(); i++)
		SetUpBuffers(reflecBarrierModel->meshes[i].VAO, refleModelMatrices, amount);
}

Barriers::~Barriers()
{
	delete barrierModel;
	delete reflecBarrierModel;
	delete[] modelMatrices;
	delete[] refleModelMatrices;
}

void Barriers::Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();

	UseInstancingShader();
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "view"), 1, GL_FALSE, &view.data[0]);

	RenderInstance(barrierModel, amount);
}

void Barriers::RenderReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();

	UseInstancingShader();
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID(), "view"), 1, GL_FALSE, &view.data[0]);

	RenderInstance(reflecBarrierModel, amount);
}