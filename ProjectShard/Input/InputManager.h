#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW\glfw3.h>
#include "..\Math\Vector2.h"
#include <iostream>

#define CONTROLLER_ONE   0
#define CONTROLLER_TWO   1
#define CONTROLLER_THREE 2
#define CONTROLLER_FOUR  3

#define XBOX360_A		0
#define XBOX360_B		1
#define XBOX360_X		2
#define XBOX360_Y		3
#define XBOX360_LB		4
#define XBOX360_RB		5
#define XBOX360_LEFT_JOY_BUTTON	 6
#define XBOX360_RIGHT_JOY_BUTTON 7
#define XBOX360_BACK	8
#define XBOX360_START	9
#define XBOX360_UP		10
#define XBOX360_RIGHT	11
#define XBOX360_DOWN	12
#define XBOX360_LEFT	13

#define XBOX360_MAX_BUTTONS 14

#define LEFT_STICK_X	0
#define LEFT_STICK_Y	1
#define TRIGGERS		2
#define RIGHT_STICK_Y	3
#define RIGHT_STICK_X	4

struct XboxControllerState
{
	Vector2 leftThumbStick, rightThumbStick;
	float leftTrigger, rightTrigger;

	union
	{
		bool buttons[XBOX360_MAX_BUTTONS];
		struct
		{
			bool A;
			bool B;
			bool X;
			bool Y;
			bool LB;
			bool RB;
			bool back;
			bool start;
			bool leftThumbStickClick;
			bool rightThumbStickClick;
			bool DpadUp;
			bool DpadDown;
			bool DpadLeft;
			bool DpadRight;
		};
	};
};

// A singleton Input Manager class
class InputManager
{
private:
	GLFWwindow *window;
	InputManager();
	const float *axis;
	int count;
	unsigned int controllerIndex;

public:
	static const int MAX_KEYS = 1024;
	bool keys_down[MAX_KEYS];
	bool keys_locked[MAX_KEYS];
	std::string keyInput;
	XboxControllerState currentControllerState;
	XboxControllerState previousControllerState;
	const float DPAD_THRESHHOLD = 0.2f;

	void SetControllerIndex(unsigned int controllerIndex);
	static InputManager &GetInstance();
	bool IsKeyPressed(int key);
	bool IsKeyDown(int key);
	bool IsMouseButtonPressed(int key);
	Vector2 GetCursorPos();
	void SetWindowContext(GLFWwindow *currentWindow);
	bool IsJoyStickPresent(int joyStick);
	bool IsControllerButtonPressed(unsigned int button);
	bool IsControllerButtonDown(unsigned int button);
	Vector2 GetLeftJoyStick();
	Vector2 GetRightJoyStick();
};

#endif