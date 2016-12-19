#include "GameApplication.h"

GameApplication::GameApplication(GLsizei _screenWidth, GLsizei _screenHeight)
	: screenWidth(_screenWidth), screenHeight(_screenHeight), nbFrames(0), finishedMenu(_screenWidth, _screenHeight)
{
	lastTime = glfwGetTime();

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
	finishedMenu.Init();

	msPerFrameText.Load("Resources/Fonts/arial.ttf");
}

void GameApplication::Update(GLfloat deltaTime)
{
	// ms per frame
	float currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0)
	{
		msPerFrame = 1000.0 / float(nbFrames);
		nbFrames = 0;
		lastTime += 1.0;
	}

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
				racingScene->finishedRace = false;
				racingScene->sceneBlur = false;
				racingScene->SetPlayerMovement(true);
				racingScene->SetRenderUIState(true);
				racingScene->player.recordRace = true;
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
				racingScene->player.recordRace = false;
			}

			if (racingScene->finishedRace)
			{
				currentGameState = GameState::finishedMenu;
				racingScene->sceneBlur = true;
				racingScene->SetPlayerMovement(false);
				racingScene->SetRenderUIState(false);
				racingScene->player.recordRace = false;
			}

			break;
		}

		case GameState::finishedMenu:
		{
			racingScene->UpdateScene(deltaTime);
			finishedMenu.Update();

			if (finishedMenu.selectedMainMenu)
			{
				currentGameState = GameState::mainMenu;
				racingScene->player.Spawn();
				finishedMenu.selectedMainMenu = false;
				racingScene->player.WriteRecordedPositions();
			}
			else if (finishedMenu.selectedPlayAgain)
			{
				currentGameState = GameState::inGame;
				racingScene->player.Spawn();
				racingScene->finishedRace = false;
				racingScene->sceneBlur = false;
				racingScene->SetPlayerMovement(true);
				racingScene->SetRenderUIState(true);
				finishedMenu.selectedPlayAgain = false;
				racingScene->player.WriteRecordedPositions();
			}

			break;
		}
	}
}

void GameApplication::Render(bool windowResized)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	stringstream ss;
	ss << "ms per frame: " << msPerFrame;
	msPerFrameText.RenderText(ss.str(), Vector2(10.0f, screenHeight - 30.0f), 0.4f, Vector3(0.0, 1.0f, 0.0f), screenWidth, screenHeight);
	glDisable(GL_BLEND);

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

		case GameState::finishedMenu:
		{
			finishedMenu.Render(screenWidth, screenHeight);
			racingScene->RenderScene(screenWidth, screenHeight, windowResized);
			break;
		}
	}
}

bool GameApplication::GetCloseState()
{
	return mainMenu->exitGame;
}