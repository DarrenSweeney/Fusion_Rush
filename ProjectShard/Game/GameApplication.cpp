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
		case GameState::splashScreen:
		{
			splashScreen.Update(deltaTime);

			if (splashScreen.changeScene)
			{
				currentGameState = GameState::mainMenu;
			}

			break;
		}

		case GameState::mainMenu:
		{
			mainMenu->UpdateScene(deltaTime, screenWidth, screenHeight);
			if (mainMenu->playGame)
			{
				currentGameState = GameState::inGame;
				racingScene->sceneBlur = false;
				racingScene->SetPlayerMovement(true);
				racingScene->SetRenderUIState(true);
			}
			break;
		}


		case GameState::inGame:
		{
			racingScene->UpdateScene(deltaTime);

			if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_ESCAPE)
				|| InputManager::GetInstance().IsControllerButtonPressed(XBOX360_BACK))
			{
				currentGameState = GameState::mainMenu;
				racingScene->sceneBlur = true;
				racingScene->SetPlayerMovement(false);
				racingScene->SetRenderUIState(false);
			}

			break;
		}
	}
}

void GameApplication::Render(bool windowResized)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	switch (currentGameState)
	{
		case GameState::splashScreen:
		{
			splashScreen.Render(screenWidth, screenHeight);

			break;
		}

		case GameState::mainMenu:
		{
			mainMenu->RenderScene(screenWidth, screenHeight);
			racingScene->RenderScene(screenWidth, screenHeight, windowResized);
			break;
		}

		case GameState::inGame:
		{
			racingScene->RenderScene(screenWidth, screenHeight, windowResized);
			break;
		}
	}
}

bool GameApplication::GetCloseState()
{
	return mainMenu->exitGame;
}