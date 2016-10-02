#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW\glfw3.h>
#include "..\Math\Vector2.h"

// A singleton Input Manager class
class InputManager
{
private:
	GLFWwindow *window;
	InputManager();

public:
	static InputManager &GetInstance();

	bool IsKeyPressed(int key);
	bool IsMouseButtonPressed(int key);
	Vector2 GetCursorPos();
	void SetWindow(GLFWwindow *currentWindow);
};

#endif