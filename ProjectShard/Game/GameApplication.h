#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "..\Core\ResourceManager.h"
#include "RacingScene.h"
#include "MainMenu.h"
#include "SplashScreen.h"

class GameApplication
{
private:
	SplashScreen splashScreen;
	MainMenu *mainMenu;
	RacingScene *racingScene;

	enum class GameState
	{
		splashScreen,
		mainMenu,
		inGame
	};
	GameState currentGameState = GameState::splashScreen;

public:
	GameApplication(GLsizei screenWidth, GLsizei screenHeight);
	~GameApplication();

	void Init();
	void Update(GLfloat deltaTime);
	void Render(bool windowResized);
	bool GetCloseState();

	GLsizei screenWidth, screenHeight;
};

#endif