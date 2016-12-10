#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "..\Core\ResourceManager.h"
#include "RacingScene.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "FinishedMenu.h"

class GameApplication
{
private:
	SplashScreen splashScreen;
	MainMenu *mainMenu;
	RacingScene *racingScene;
	FinishedMenu finishedMenu;

	// ms per frame
	double lastTime;
	int nbFrames;
	double msPerFrame;
	Text msPerFrameText;

	enum class GameState
	{
		splashScreen,
		mainMenu,
		inGame,
		finishedMenu,
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