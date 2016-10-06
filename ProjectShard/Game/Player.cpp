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

	Quaternion from = Quaternion();

	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_UP))
		linearVelocity.z -= 0.30f;
	else if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_DOWN))
		linearVelocity.z += 0.30f;

	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_LEFT))
	{
		linearVelocity.x -= 0.20f;

		Quaternion to = Quaternion();
		to = to.RotateZ(MathHelper::DegressToRadians(90.0f));
		orientation = orientation.Slerp(orientation, to, deltaTime * rotationSpeed);
	}
	else
		orientation = orientation.Slerp(orientation, from, deltaTime * rotationSpeed);
	
	if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_RIGHT))
	{
		linearVelocity.x += 0.20f;

		Quaternion to = Quaternion();
		to = to.RotateZ(MathHelper::DegressToRadians(-90.0f));
		orientation = orientation.Slerp(orientation, to, deltaTime * rotationSpeed);
	}
	else
		orientation = orientation.Slerp(orientation, from, deltaTime * rotationSpeed);

	if (linearVelocity.x != 0)
	{
		Vector3 i = linearVelocity;
		float friction = 0.003f;

		linearVelocity -= i * friction;
	}

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	const float *axis = NULL;
	int count;
	if (1 == present)
	{
		axis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

		// Movement - Left Stick
		if (axis[0] < -0.2)
		{
			linearVelocity.x -= 0.20f;

			Quaternion to = Quaternion();
			to = to.RotateZ(MathHelper::DegressToRadians(90.0f));
			orientation = orientation.Slerp(orientation, to, deltaTime * rotationSpeed);
		}

		if (axis[0] > 0.2)
		{
			linearVelocity.x += 0.20f;

			Quaternion to = Quaternion();
			to = to.RotateZ(MathHelper::DegressToRadians(-90.0f));
			orientation = orientation.Slerp(orientation, to, deltaTime * rotationSpeed);
		}

		if (axis[4] > 0.2)
		{
			linearVelocity.z -= 0.30f;
		}

		if (axis[5] > 0.2)
		{
			linearVelocity.z += 0.30f;
		}
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