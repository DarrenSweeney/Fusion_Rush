#include "GameApplication.h"

GameApplication::GameApplication()
	: lastX(0.0f), lastY(0.0f), activeCamera(false)
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
	testPlayArea->UpdateScene(deltaTime);

	Vector2 cursorPos = InputManager::GetInstance().GetCursorPos();
	GLfloat xOffset = cursorPos.x - lastX;
	GLfloat yOffset = lastY - cursorPos.y;
	lastX = cursorPos.x;
	lastY = cursorPos.y;

	if (InputManager::GetInstance().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
		activeCamera = true;
	else
		activeCamera = false;
}

void GameApplication::Render(GLsizei screenWidth, GLsizei screenHeight)
{
	testPlayArea->RenderScene(screenWidth, screenHeight);
	//g_debugDrawMgr.Submit(player.camera);
}