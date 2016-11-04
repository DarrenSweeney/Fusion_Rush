#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "..\Core\ResourceManager.h"
#include "TestPlayArea.h"
#include "MainMenu.h"

class GameApplication
{
private:
	TestPlayArea *testPlayArea;
	MainMenu *mainMenu;
	GLsizei screenWidth, screenHeight;

	enum class GameState
	{
		mainMenu,
		inGame
	};
	GameState currentGameState = GameState::mainMenu;

public:
	GameApplication(GLsizei screenWidth, GLsizei screenHeight);
	~GameApplication();
	void Init();
	void Update(GLfloat deltaTime);
	void Render();
};

#endif