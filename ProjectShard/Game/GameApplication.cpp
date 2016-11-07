#include "GameApplication.h"

GameApplication::GameApplication(GLsizei _screenWidth, GLsizei _screenHeight)
	: screenWidth(_screenWidth), screenHeight(_screenHeight)
{
	racingScene = new RacingScene();
	mainMenu = new MainMenu();
}

GameApplication::~GameApplication()
{
	delete racingScene;
	delete mainMenu;
}

void GameApplication::Init()
{
	racingScene->InitalizeScene(screenWidth, screenHeight);
	mainMenu->InitScene();
}

void GameApplication::Update(GLfloat deltaTime)
{
	switch (currentGameState)
	{
		case GameState::mainMenu:
		{
			mainMenu->UpdateScene(deltaTime);
			break;
		}
	}

	racingScene->UpdateScene(deltaTime);
}

void GameApplication::Render(bool windowResized)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	switch (currentGameState)
	{
		case GameState::mainMenu:
		{
			mainMenu->RenderScene(screenWidth, screenHeight);
			break;
		}
	}

	racingScene->RenderScene(screenWidth, screenHeight, windowResized);
}