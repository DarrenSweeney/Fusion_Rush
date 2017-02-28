#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "RacingScene.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "FinishedMenu.h"
#include "..\GameSparksInfo.h"

class GameApplication
{
private:
	SoundEngine soundEngine;

	SplashScreen splashScreen;
	MainMenu *mainMenu;
	RacingScene *racingScene;
	FinishedMenu *finishedMenu;
	Shader *crtShader;
	GLuint framebuffer, quadVAO, texColorBuffer;

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

	void SetUpBuffers(GLsizei screenWidth, GLsizei screenHeight);
	void reset();

public:
	GameApplication(GLsizei _screenWidth, GLsizei _screenHeight);
	~GameApplication();

	void Init();
	void Update(GLfloat deltaTime);
	void Render(bool windowResized);
	bool GetCloseState();

	GLsizei screenWidth, screenHeight;
};

#endif