#include "Player.h"

Player::Player()
	: rotationSpeed(2.0f)
{
	model = g_resourceMgr.GetModel(SID("PlayerShip"));
	shaderModel = g_resourceMgr.GetShader(SID("ModelShader"));
}

Player::~Player()
{
	delete model;
	delete shaderModel;
}

void Player::Update(float deltaTime)
{
	position += linearVelocity * deltaTime;

	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_UP))
	{
		linearVelocity.z -= 0.08f;
	}

	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_LEFT))
	{
		linearVelocity.x -= 0.08f;

		Quaternion from = Quaternion();
		Quaternion to = Quaternion();
		to = to.RotateZ(MathHelper::DegressToRadians(90.0f));
		orientation = orientation.Slerp(orientation, to, deltaTime * rotationSpeed);
	}
	else
	{
		Quaternion from = Quaternion();
		orientation = orientation.Slerp(orientation, from, deltaTime * rotationSpeed);
	}
	
	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_RIGHT))
	{
		linearVelocity.x += 0.08f;

		Quaternion from = Quaternion();
		Quaternion to = Quaternion();
		to = to.RotateZ(MathHelper::DegressToRadians(-90.0f));
		orientation = orientation.Slerp(orientation, to, deltaTime * rotationSpeed);
	}
	else
	{
		Quaternion from = Quaternion();
		orientation = orientation.Slerp(orientation, from, deltaTime * rotationSpeed);
	}
}

void Player::Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	shaderModel->Use();
	Matrix4 modelMatrix = Matrix4();
	Matrix4 viewMatrix = camera.GetViewMatrix();
	Matrix4 projection = Matrix4();
	projection = projection.perspectiveProjection(camera.zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);
	Matrix4 modelScale = Matrix4();
	//modelScale = modelScale.scale(Vector3(0.04f, 0.04f, 0.04f));
	Matrix4 modelRotate = Matrix4();
	modelRotate = modelRotate.QuaternionToMatrix4(orientation);
	Matrix4 modelTranslate = Matrix4();
	modelTranslate = modelTranslate.translate(position);
	modelMatrix = modelScale * modelRotate * modelTranslate;
	glUniformMatrix4fv(glGetUniformLocation(shaderModel->Program, "model"), 1, GL_FALSE, &modelMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderModel->Program, "view"), 1, GL_FALSE, &viewMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderModel->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	model->Draw(*shaderModel);
}