#include "Player.h"

Player::Player()
	: rotationSpeed(2.0f), camera(Vector3(3.0f, 0.0f, 2.0)), position(Vector3(0.0f, 0.0f, 150.0f))
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
	camera.position = position - Vector3(0.0f, -15.0f, -40.0f);

	Quaternion targetRotation = Quaternion();
	Quaternion initalRotation = Quaternion();

	// Input for controller 1
	const float *axis = InputManager::GetInstance().GetJoyStickAxis(GLFW_JOYSTICK_1);

	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_UP) || axis[LEFT_TRIGGER] > 0.2)
		linearVelocity.z -= 0.9f;
	else if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_DOWN) || axis[RIGHT_TRIGGER] > 0.2)
		linearVelocity.z += 0.9f;

	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_LEFT) || axis[LEFT_STICK_X] < -0.2)
	{
		linearVelocity.x -= 0.9f;

		targetRotation = targetRotation.RotateZ(MathHelper::DegressToRadians(90.0f));
		orientation = orientation.Slerp(orientation, targetRotation, deltaTime * rotationSpeed);
	}
	else
		orientation = orientation.Slerp(orientation, initalRotation, deltaTime * rotationSpeed);
	
	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_RIGHT) || axis[LEFT_STICK_X] > 0.2)
	{
		linearVelocity.x += 0.9f;

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
}

void Player::Render(GLsizei screenWidth, GLsizei screenHeight)
{
	shaderModel->Use();
	Matrix4 modelMatrix = Matrix4();
	Matrix4 viewMatrix = camera.GetViewMatrix();
	Matrix4 projection = Matrix4();
	projection = projection.perspectiveProjection(camera.zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 1000.0f);
	Matrix4 modelScale = Matrix4();
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