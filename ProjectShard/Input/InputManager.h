#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW\glfw3.h>
#include "..\Math\Vector2.h"
#include <iostream>

// NOTE(Darren): This could be incorrect becuase i'm using a PS4 controller.
#define LEFT_STICK_X	0
#define LEFT_STICK_Y	1
#define RIGHT_STICK_X	2
#define RIGHT_STICK_Y	3
#define LEFT_TRIGGER	4
#define RIGHT_TRIGGER	5

// A singleton Input Manager class
class InputManager
{
private:
	GLFWwindow *window;
	InputManager();
	const float *axis;
	int count;

public:
	static InputManager &GetInstance();
	bool IsKeyPressed(int key);
	bool IsKeyDown(int key);
	bool IsMouseButtonPressed(int key);
	Vector2 GetCursorPos();
	void SetWindowContext(GLFWwindow *currentWindow);
	bool IsJoyStickPresent(int joyStick); // NOTE(Darren): support for 16 joysticks?
	const float *GetJoyStickAxis(int joystick);
	const unsigned char *GetJoyStickButtons(int joystick);
	static const int MAX_KEYS = 1024;
	bool keys_down[MAX_KEYS];
	bool keys_locked[MAX_KEYS];
	std::string keyInput;
};

#endif