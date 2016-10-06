#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "TestPlayArea.h"

class GameApplication
{
private:
	TestPlayArea *testPlayArea;
	GLfloat lastX;
	GLfloat lastY;
	bool activeCamera;

public:
	GameApplication();
	~GameApplication();
	void Init();
	void Update(GLfloat deltaTime);
	void Render(GLsizei screenWidth, GLsizei screenHeight);
};

#endif