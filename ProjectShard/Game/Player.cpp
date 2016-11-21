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

	// TODO(Darren): Take out the dead zone from here
	float deadZone = 0.2f;

	// TODO(Darren): Need to implement the defines for a 360 controller and create 
	// a correct input button method where i don't need to check if a controller is connected
	// Input for controller 1
	bool connected = InputManager::GetInstance().IsJoyStickPresent(GLFW_JOYSTICK_3);
	const float *axis = InputManager::GetInstance().GetJoyStickAxis(GLFW_JOYSTICK_3);
	const unsigned char* buttons = InputManager::GetInstance().GetJoyStickButtons(GLFW_JOYSTICK_3);

	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_UP) || (connected && axis[LEFT_TRIGGER] > deadZone)
		|| (connected && buttons[5] == GLFW_PRESS))
		linearVelocity.z -= speed;

	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_DOWN) || (connected && axis[RIGHT_TRIGGER] > deadZone)
		|| (connected && buttons[4] == GLFW_PRESS))
		linearVelocity.z += speed * 2.0f;

	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_LEFT) || (connected && axis[LEFT_STICK_X] < -deadZone))
	{
		linearVelocity.x -= speed;

		targetRotation = targetRotation.RotateZ(MathHelper::DegressToRadians(90.0f));
		orientation = orientation.Slerp(orientation, targetRotation, deltaTime * rotationSpeed);
	}
	else
		orientation = orientation.Slerp(orientation, initalRotation, deltaTime * rotationSpeed);

	if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_RIGHT) || (connected && axis[LEFT_STICK_X] > deadZone))
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