#include "TrackBlock.h"

TrackBlock::TrackBlock()
	:	position(10.5f, 0.5f, -550.0f), scaleVec(7.0f, 7.0f, 7.0f)
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

void TrackBlock::Update(float deltaTime)
{
	// Generate a sector ID here based on z position 
	sectorID = int(fabs(position.z) / 100.0f);

	switch (blockType)
	{
	case oscillation:
		OscillationUpdate(deltaTime);
		break;

	case rotating:
		RotatingUpdate(deltaTime);
		break;

	default:
		break;
	}

	boundingBox.UpdateBoundingBox(position, rotate, scaleVec);
}

void TrackBlock::OscillationUpdate(float deltaTime)
{
	float movementSpeed = 2.0f;
	Vector3 targetUp(position.x, 2.0f, position.z);
	Vector3 targetDown(position.x, 45.0f, position.z);

	if (!moveToTarget)
	{
		position = position.Lerp(position, targetUp, movementSpeed * deltaTime);
	}
	else if (moveToTarget)
	{
		position = position.Lerp(position, targetDown, movementSpeed * deltaTime);
	}

	if (position.y >= targetDown.y - 1)
		moveToTarget = false;

	if (position.y <= targetUp.y + 1)
		moveToTarget = true;
}

void TrackBlock::RotatingUpdate(float deltaTime)
{
	Vector3 targetLeft(-45.0f, position.y, position.z);
	Vector3 targetRight(45.0f, position.y, position.z);
	float movementSpeed = 2.0f;
	Quaternion rotation = Quaternion();
	Quaternion targetRotation = Quaternion();

	if (!moveToTarget)
	{
		targetRotation = targetRotation.RotateZ(MathHelper::DegressToRadians(90.0f));
		position = position.Lerp(position, targetLeft, movementSpeed * deltaTime);
		rotation = rotation.Slerp(rotation, targetRotation, deltaTime * 1.0f);
	}
	else if (moveToTarget)
	{
		targetRotation = targetRotation.RotateZ(MathHelper::DegressToRadians(-90.0f));
		position = position.Lerp(position, targetRight, movementSpeed * deltaTime);
		rotation = rotation.Slerp(rotation, targetRotation, deltaTime * 1.0f);
	}

	if (position.x >= targetRight.x - 1)
		moveToTarget = false;

	if (position.x <= targetLeft.x + 1)
		moveToTarget = true;

	Matrix4 modelRotate = Matrix4();
	modelRotate = modelRotate.QuaternionToMatrix4(rotation);
	rotate = rotate * modelRotate;
}

void TrackBlock::Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 view = camera.GetViewMatrix();
	Matrix4 model = Matrix4();
	Matrix4 translate = Matrix4();
	Matrix4 scale = Matrix4();

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

	Matrix4 mirror = Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
							 0.0f, -1.0f, 0.0f, 0.0f, 
							 0.0f, 0.0f, 1.0f, 0.0f,
							 0.0f, 0.0f, 0.0f, 1.0f);

	shaderBlock->Use();
	translate = translate.translate(Vector3(position.x, -position.y - 5.0f, position.z));
	scale = Matrix4();
	scale = scale.scale(scaleVec);
	model = scale * rotate * translate;
	shaderBlock->Use();
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "view"), 1, GL_FALSE, &view.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderBlock->Program, "model"), 1, GL_FALSE, &model.data[0]);
	modelBlock->Draw(*shaderBlock);
}