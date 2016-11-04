#include "GameApplication.h"

GameApplication::GameApplication(GLsizei _screenWidth, GLsizei _screenHeight)
	: screenWidth(_screenWidth), screenHeight(_screenHeight)
{
	testPlayArea = new TestPlayArea();
	mainMenu = new MainMenu();
}

GameApplication::~GameApplication()
{
	delete testPlayArea;
	delete mainMenu;
}

void GameApplication::Init()
{
	testPlayArea->InitalizeScene(screenWidth, screenHeight);
	mainMenu->InitScene();
}

void GameApplication::Update(GLfloat deltaTime)
{
	mainMenu->UpdateScene(deltaTime);
	testPlayArea->UpdateScene(deltaTime);

	/*switch (currentGameState)
	{
		case GameState::mainMenu:
		{
			mainMenu->UpdateScene(deltaTime);
			break;
		}

		case GameState::inGame:
		{
			testPlayArea->UpdateScene(deltaTime);
			break;
		}
	}*/
}

void GameApplication::Render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	testPlayArea->RenderScene(screenWidth, screenHeight);
	mainMenu->RenderScene(screenWidth, screenHeight);

	/*switch (currentGameState)
	{
		case GameState::mainMenu:
		{
			mainMenu->RenderScene(screenWidth, screenHeight);
			break;
		}

		case GameState::inGame:
		{
			testPlayArea->RenderScene(screenWidth, screenHeight);
			break;
		}
	}*/
}