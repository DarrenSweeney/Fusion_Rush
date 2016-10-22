#include "TrackBlock.h"

TrackBlock::TrackBlock()
	:	position(10.5f, 0.5f, -550.0f)
{
	modelBlock = g_resourceMgr.GetModel("Block");
	shaderBlock = g_resourceMgr.GetShader("ModelShader");
	rotate = Matrix4();
}

TrackBlock::~TrackBlock()
{
	delete modelBlock;
	delete shaderBlock;
}

void TrackBlock::Update()
{
	// Generate a sector ID here based on z position 
	sectorID = int(fabs(position.z) / 100.0f);

	switch (blockType)
	{
	case oscillation:
		OscillationUpdate();
		break;

	case rotating:
		RotatingUpdate();
		break;

	default:
		break;
	}

	//rotate = rotate.rotate(MathHelper::DegressToRadians(45.0f), Vector3(-0.9f, 0.2f, -0.5f));
	Vector3 scaleVec = Vector3(7.0f, 7.0f, 7.0f);

	// Only update the collison if it's not moving in the scene
	//if(!blockType == BlockType::stationary)		// TODO(Darren): Implement this
		boundingBox.UpdateBoundingBox(position, rotate, scaleVec);
}

void TrackBlock::OscillationUpdate()
{
	position.y = 11.0f + cos(glfwGetTime()) * 5.0f;
}

void TrackBlock::RotatingUpdate()
{

}

void TrackBlock::Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();

	Vector3 scaleVec = Vector3(7.0f, 7.0f, 7.0f);
	shaderBlock->Use();
	translate = translate.translate(position);
	scale = Matrix4();
	scale = scale.scale(scaleVec);
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

	Vector3 scaleVec = Vector3(7.0f, 7.0f, 7.0f);
	shaderBlock->Use();
	translate = translate.translate(Vector3(position.x, -position.y - 5.0f, position.z));
	scale = Matrix4();
	scale = scale.scale(scaleVec);
	// TODO(Darren): Create a rotation reflection (look into this)
	model = scale * rotate * translate;
	shaderBlock->Use();
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "model"), 1, GL_FALSE, &model.data[0]);
	modelBlock->Draw(*shaderBlock);
}