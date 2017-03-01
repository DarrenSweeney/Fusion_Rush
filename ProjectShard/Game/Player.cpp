#include "Player.h"

PlayerShip::PlayerShip()
	: rotationSpeed(2.5f), camera(Vector3(3.0f, 2.0f, 8.0f)), position(Vector3(0.0f, 0.0f, 0.0f)), 
	speed(2.0f), recordRace(false), lastTime(0.0f), frictionToApply(0.003f)
{
	model = g_resourceMgr.GetModel(SID("PlayerShip"));
	shaderModel = g_resourceMgr.GetShader(SID("PlayerShader"));

	shaderModel->Use();
	glUniform1f(glGetUniformLocation(shaderModel->Program, "time"), 0.0f);
}

PlayerShip::~PlayerShip()
{
	delete model;
	delete shaderModel;
}

void PlayerShip::Update(float deltaTime, float currentRaceTime)
{
	if (InputManager::GetInstance().controllerIndex == -1)
		KeyboardMovement(deltaTime);
	else
		SteeringWheelMovement(deltaTime);

	if (InputManager::GetInstance().IsControllerButtonPressed(XBOX360_START)
		|| InputManager::GetInstance().IsKeyPressed(GLFW_KEY_R))
	{
		Spawn();
	}

	if (shipDestroyed)
	{
		PlayExplodeAnimation(deltaTime);
	}

	Vector3 initPos = Vector3(3.0f, 2.0f, 8.0f);
	Vector3 finalPos = position - Vector3(0.0f, -15.0f, -40.0f);

	if (cameraInterpolator < 1.0f)
		cameraInterpolator += 0.8f * deltaTime;
	else
		cameraInterpolator = 1.0f;

	Vector3 transitionVector = transitionVector.Lerp(initPos, finalPos, cameraInterpolator);

	Vector3 direction = position - camera.GetPosition();

	camera.SetPosition(transitionVector);

	modelRotate = Matrix4();
	modelRotate = modelRotate.QuaternionToMatrix4(orientation);
	boundingBox.UpdateBoundingBox(position, modelRotate, Vector3(1.0f, 1.0f, 1.0f));

	RecordPosition(currentRaceTime);

	currentTrackTime += deltaTime;

	oldPosition = position;
}

void PlayerShip::FinishedAnimation(float deltaTime, Vector3 endRacePos)
{
	Vector3 initPos = position - Vector3(0.0f, -15.0f, -40.0f);
	Vector3 finalPos = initPos - Vector3(-10.0f, 5.0f, 15.0f);
	frictionToApply = 0.020f;

	if (finishedCameraInterpolation < 1.0f)
		finishedCameraInterpolation += 0.4f * deltaTime;
	else
		finishedCameraInterpolation = 1.0f;

	Vector3 transitionVector = transitionVector.Lerp(initPos, finalPos, finishedCameraInterpolation);

	orientation = orientation.Slerp(orientation, Quaternion(), deltaTime * rotationSpeed);

	camera.SetPosition(transitionVector);
}

void PlayerShip::PlayExplodeAnimation(float deltaTime)
{
	explodeMagnitude += 20.0f * deltaTime;

	// Add time component to geometry shader in the form of a uniform
	shaderModel->Use();
	glUniform1f(glGetUniformLocation(shaderModel->Program, "magnitude"), explodeMagnitude);

	if (explodeMagnitude > 20.0f)
	{
		Spawn();
		shipSpawned = true;
	}
}

void PlayerShip::KeyboardMovement(float deltaTime)
{
	if (linearVelocity.Magnitude() < 0.5f)
		linearVelocity = Vector3();

	position += linearVelocity * deltaTime;

	if (updateMovement && !shipDestroyed)
	{
		Quaternion targetRotation = Quaternion();
		Quaternion initalRotation = Quaternion();

		if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_UP))
			linearVelocity.z -= speed;

		if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_DOWN))
			linearVelocity.z += speed * 2.0f;

		if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_LEFT))
		{
			linearVelocity.x -= speed * 1.1f;

			targetRotation = targetRotation.RotateZ(MathHelper::DegressToRadians(90.0f));
			orientation = orientation.Slerp(orientation, targetRotation, deltaTime * rotationSpeed);
		}
		else
			orientation = orientation.Slerp(orientation, initalRotation, deltaTime * rotationSpeed);

		if (InputManager::GetInstance().IsKeyDown(GLFW_KEY_RIGHT))
		{
			linearVelocity.x += speed * 1.1f;

			targetRotation = targetRotation.RotateZ(MathHelper::DegressToRadians(-90.0f));
			orientation = orientation.Slerp(orientation, targetRotation, deltaTime * rotationSpeed);
		}
		else
			orientation = orientation.Slerp(orientation, initalRotation, deltaTime * rotationSpeed);
	}

	if (!(linearVelocity == Vector3()))
	{
		Vector3 i = linearVelocity;
		linearVelocity -= i * frictionToApply;
	}

#if DEBUG
	Vector3 direction = linearVelocity;
	direction.normalise();
	g_debugDrawMgr.AddLine(position, Vector3(0.0f, 10.0f, 0.0), Vector3(1.0f, 0.0f, 0.0f), 1.0f, false);
#endif
}

void PlayerShip::SteeringWheelMovement(float deltaTime)
{
	if (linearVelocity.Magnitude() < 0.5f)
		linearVelocity = Vector3();

	position += linearVelocity * deltaTime;

	if (updateMovement && !shipDestroyed)
	{
		Quaternion targetRotation = Quaternion();
		Quaternion initalRotation = Quaternion();

		if (InputManager::GetInstance().GetLeftTrigger() < -0.3f)
		{
			linearVelocity.z += speed + (abs(InputManager::GetInstance().GetLeftTrigger()) * speed * 5.0f);
		}
		else if (InputManager::GetInstance().GetRightTrigger() > -0.1f)
		{
			linearVelocity.z -= speed + (abs(InputManager::GetInstance().GetLeftTrigger()) * speed);
		}

		if (InputManager::GetInstance().GetLeftJoyStick().x < -JOYSTICK_DEAD_ZONE)
		{
			linearVelocity.x -= speed + (abs(InputManager::GetInstance().GetLeftJoyStick().x) * speed);

			targetRotation = targetRotation.RotateZ(MathHelper::DegressToRadians(90.0f));
			orientation = orientation.Slerp(orientation, targetRotation, deltaTime * rotationSpeed);
		}
		else
			orientation = orientation.Slerp(orientation, initalRotation, deltaTime * rotationSpeed);

		if (InputManager::GetInstance().GetLeftJoyStick().x > JOYSTICK_DEAD_ZONE)
		{
			linearVelocity.x += speed + (abs(InputManager::GetInstance().GetLeftJoyStick().x) * speed);

			targetRotation = targetRotation.RotateZ(MathHelper::DegressToRadians(-90.0f));
			orientation = orientation.Slerp(orientation, targetRotation, deltaTime * rotationSpeed);
		}
		else
			orientation = orientation.Slerp(orientation, initalRotation, deltaTime * rotationSpeed);
	}

	if (!(linearVelocity == Vector3()))
	{
		Vector3 i = linearVelocity;
		linearVelocity -= i * frictionToApply;
	}
}

void PlayerShip::RecordPosition(float currentRaceTime)
{
	if (recordRace)
	{
		if (currentRaceTime - lastTime >= 1.0)
		{
			lastTime += 1.0;

			Vector3 pos = position;
			recordPositions.push_back(pos);

			Quaternion orien = orientation;
			recordOrientation.push_back(orien);
		}
	}
}

void PlayerShip::WriteRecordedGhostData(float raceTime)
{
	std::ofstream ghostRacerFile;
	ghostRacerFile.open("Ghost_Racer.txt");
	ghostRacerFile << raceTime << "\n";
	ghostRacerFile << "Positions" << "\n";
	// Add the starting position
	ghostRacerFile << 0 << " " << 0 << " " << 0 << "\n";
	for (std::vector<Vector3>::iterator it = recordPositions.begin(); it != recordPositions.end(); it++)
	{
		ghostRacerFile << it->x << " " << it->y << " " << it->z << "\n";
	}

	ghostRacerFile << "Orientations" << "\n";

	// Add the starting orientation
	ghostRacerFile << 1 << " " << 0 << " " << 0 << " " << 0 << "\n";
	for (std::vector<Quaternion>::iterator it = recordOrientation.begin(); it != recordOrientation.end(); it++)
	{
		ghostRacerFile << it->w << " " << it->x << " " << it->y << " " << it->z << "\n";
	}
	ghostRacerFile.close();
}

void PlayerShip::Spawn()
{
	position = Vector3();
	orientation = Quaternion();
	linearVelocity = Vector3();
	cameraInterpolator = 0.0f;
	shaderModel->Use();
	explodeMagnitude = 0.0f;
	glUniform1f(glGetUniformLocation(shaderModel->Program, "magnitude"), explodeMagnitude);
	shipDestroyed = false;
	recordPositions.clear();
	recordOrientation.clear();
	finishedCameraInterpolation = 0.0f;
	frictionToApply = 0.003f;
	lastTime = 0.0f;
}

void PlayerShip::Render(GLsizei screenWidth, GLsizei screenHeight)
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

void PlayerShip::Reflection(GLsizei screenWidth, GLsizei screenHeight)
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

float PlayerShip::GetSpeed()
{
	return linearVelocity.Magnitude();
}