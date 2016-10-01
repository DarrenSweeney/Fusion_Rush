#include "GameApplication.h"

GameApplication::GameApplication()
	: camera(Vector3(0.0f, 3.0f, 3.0f)), lastX(0.0f), lastY(0.0f), activeCamera(false)
{
	testPlayArea = new TestPlayArea();
}

GameApplication::~GameApplication()
{
	delete testPlayArea;
}

void GameApplication::Init()
{
	testPlayArea->InitalizeScene();
}

void GameApplication::Update(GLfloat deltaTime)
{
	camera.KeyboardMovement(deltaTime);
	camera.ControllerMovement();
	testPlayArea->UpdateScene();

	Vector2 cursorPos = InputManager::GetInstance().GetCursorPos();
	GLfloat xOffset = cursorPos.x - lastX;
	GLfloat yOffset = lastY - cursorPos.y;
	lastX = cursorPos.x;
	lastY = cursorPos.y;

	if (InputManager::GetInstance().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
		activeCamera = true;
	else
		activeCamera = false;

	if (activeCamera)
		camera.MouseMovement(xOffset, yOffset);
}

void GameApplication::Render()
{
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	testPlayArea->RenderScene(camera);
	//g_debugDrawMgr.Submit(camera);
}