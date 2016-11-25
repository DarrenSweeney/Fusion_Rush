#include "Player.h"

Player::Player()
	: rotationSpeed(2.0f), camera(Vector3(3.0f, 0.0f, 2.0)), position(Vector3(0.0f, 0.0f, 50.0f)), speed(2.5f)
{
	model = g_resourceMgr.GetModel(SID("PlayerShip"));
	shaderModel = g_resourceMgr.GetShader(SID("PlayerShader"));
}

Player::~Player()
{
	delete model;
	delete shaderModel;
}

void Player::Update(float deltaTime)
{
	// Add time component to geometry shader in the form of a uniform
	shaderModel->Use();
	glUniform1f(glGetUniformLocation(shaderModel->Program, "time"), glfwGetTime() * 5.0f);

	if(updateMovement)
		Movement(deltaTime);

	camera.SetPosition(position - Vector3(0.0f, -15.0f, -40.0f));

	modelRotate = Matrix4();
	modelRotate = modelRotate.QuaternionToMatrix4(orientation);
	boundingBox.UpdateBoundingBox(position, modelRotate, Vector3(1.0f, 1.0f, 1.0f));
}

void Player::Movement(float deltaTime)
{
	position += linearVelocity * deltaTime;

	Quaternion targetRotation = Quaternion();
	Quaternion initalRotation = Quaternion();

	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_UP)
		|| InputManager::GetInstance().IsControllerButtonDown(XBOX360_RB))
		linearVelocity.z -= speed;

	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_DOWN)
		|| InputManager::GetInstance().IsControllerButtonPressed(XBOX360_LB))
		linearVelocity.z += speed * 2.0f;

	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_LEFT) 
		|| InputManager::GetInstance().GetLeftJoyStick().x < - JOYSTICK_DEAD_ZONE)
	{
		linearVelocity.x -= speed;

		targetRotation = targetRotation.RotateZ(MathHelper::DegressToRadians(90.0f));
		orientation = orientation.Slerp(orientation, targetRotation, deltaTime * rotationSpeed);
	}
	else
		orientation = orientation.Slerp(orientation, initalRotation, deltaTime * rotationSpeed);

	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_RIGHT) 
		|| InputManager::GetInstance().GetLeftJoyStick().x > JOYSTICK_DEAD_ZONE)
	{
		linearVelocity.x += speed;

		targetRotation = targetRotation.RotateZ(MathHelper::DegressToRadians(-90.0f));
		orientation = orientation.Slerp(orientation, targetRotation, deltaTime * rotationSpeed);
	}
	else
		orientation = orientation.Slerp(orientation, initalRotation, deltaTime * rotationSpeed);

	if (linearVelocity.x != 0)
	{
		Vector3 i = linearVelocity;
		float friction = 0.003f;

		linearVelocity -= i * friction;
	}

	Vector3 direction = linearVelocity;
	direction.normalise();
	g_debugDrawMgr.AddLine(position, Vector3(0.0f, 10.0f, 0.0), Vector3(1.0f, 0.0f, 0.0f), 1.0f, false);
}

void Player::Spawn()
{
	position = Vector3(0.0f, 0.0f, 50.0f);
	linearVelocity = Vector3();
}

void Player::Render(GLsizei screenWidth, GLsizei screenHeight)
{
	shaderModel->Use();
	Matrix4 modelMatrix = Matrix4();
	Matrix4 viewMatrix = camera.GetViewMatrix();
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 modelRotate = Matrix4();
	modelRotate = modelRotate.QuaternionToMatrix4(orientation);
	Matrix4 modelTranslate = Matrix4();
	modelTranslate = modelTranslate.translate(position);
	modelMatrix = modelRotate * modelTranslate;
	glUniformMatrix4fv(glGetUniformLocation(shaderModel->Program, "model"), 1, GL_FALSE, &modelMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderModel->Program, "view"), 1, GL_FALSE, &viewMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderModel->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	model->Draw(*shaderModel);
}

void Player::Reflection(GLsizei screenWidth, GLsizei screenHeight)
{
	shaderModel->Use();
	Matrix4 modelMatrix = Matrix4();
	Matrix4 viewMatrix = camera.GetViewMatrix();
	Matrix4 projection = camera.GetProjectionMatrix(screenWidth, screenHeight);
	Matrix4 modelRotate = Matrix4();
	Quaternion rotateRef = Quaternion();
	rotateRef = rotateRef.RotateZ(MathHelper::DegressToRadians(-180.0f));
	modelRotate = modelRotate.QuaternionToMatrix4(rotateRef * 
		Quaternion(orientation.w, -orientation.x, -orientation.y, -orientation.z));
	Matrix4 modelTranslate = Matrix4();
	modelTranslate = modelTranslate.translate(position + Vector3(0.0f, -3.0f, 0.0));
	modelMatrix = modelRotate * modelTranslate;
	glUniformMatrix4fv(glGetUniformLocation(shaderModel->Program, "model"), 1, GL_FALSE, &modelMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderModel->Program, "view"), 1, GL_FALSE, &viewMatrix.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderModel->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	model->Draw(*shaderModel);
}