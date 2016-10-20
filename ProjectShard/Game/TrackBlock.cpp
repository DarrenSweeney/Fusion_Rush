#include "TrackBlock.h"

TrackBlock::TrackBlock()
{
	modelBlock = g_resourceMgr.GetModel("Block");
	shaderBlock = g_resourceMgr.GetShader("ModelShader");
}

TrackBlock::~TrackBlock()
{
	delete modelBlock;
	delete shaderBlock;
}

void TrackBlock::Update()
{
	Vector3 translation = Vector3(10.5f, 7.5f, -550.0f);
	rotate = Matrix4();
	rotate = rotate.rotate(MathHelper::DegressToRadians(45.0f), Vector3(-0.9f, 0.2f, -0.5f));
	Vector3 scaleVec = Vector3(7.0f, 7.0f, 7.0f);
	boundingBox.UpdateBoundingBox(translation, rotate, scaleVec);
}

void TrackBlock::Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();

	Vector3 translation = Vector3(10.5f, 7.5f, -550.0f);
	Vector3 scaleVec = Vector3(7.0f, 7.0f, 7.0f);
	shaderBlock->Use();
	translate = translate.translate(translation);
	scale = Matrix4();
	scale = scale.scale(scaleVec);
	rotate = rotate.rotate(MathHelper::DegressToRadians(45.0f), Vector3(-0.9f, 0.2f, -0.5f));
	model = scale * rotate * translate;
	shaderBlock->Use();
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "model"), 1, GL_FALSE, &model.data[0]);
	modelBlock->Draw(*shaderBlock);
}

void TrackBlock::RenderReflection(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();

	Vector3 translation = Vector3(10.5f, -7.5f, -550.0f);
	Vector3 scaleVec = Vector3(7.0f, 7.0f, 7.0f);
	shaderBlock->Use();
	translate = translate.translate(translation);
	scale = Matrix4();
	scale = scale.scale(scaleVec);
	rotate = rotate.rotate(MathHelper::DegressToRadians(-45.0f), Vector3(-0.9f, 0.2f, -0.5f));
	// TODO(Darren): Create a rotation reflection (look into this)
	model = scale * rotate * translate;
	shaderBlock->Use();
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "model"), 1, GL_FALSE, &model.data[0]);
	modelBlock->Draw(*shaderBlock);
}

bool TrackBlock::HitPlayer()
{
	return false;
}