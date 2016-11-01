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
}

void GameApplication::Render(GLsizei screenWidth, GLsizei screenHeight)
{
	testPlayArea->RenderScene(screenWidth, screenHeight);
}