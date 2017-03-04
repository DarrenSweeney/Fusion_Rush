#include "InputManager.h"

InputManager::InputManager()
	: controllerIndex(NO_CONTROLLER_CONNTECTED) { }

InputManager &InputManager::GetInstance()
{
	static InputManager *instance = new InputManager();
	return *instance;
}

bool InputManager::IsKeyPressed(int key)
{
	if (keys_down[key] && !keys_locked[key]) 
	{
		keys_locked[key] = true;
		return true;
	}

	return false;
}

bool InputManager::IsKeyDown(int key)
{
	if (keys_down[key]) 
	{
		return true;
	}

	return false;
}

bool InputManager::IsMouseButtonPressed(int key)
{
	int state = glfwGetMouseButton(window, key);

	if (state == GLFW_PRESS)
		return true;
	else
		return false;
}

Vector2 InputManager::GetCursorPos()
{
	Vector2 cursorPos;
	double posX, posY;
	glfwGetCursorPos(window, &posX, &posY);
	cursorPos = Vector2(posX, posY);

	return cursorPos;
}

void InputManager::SetWindowContext(GLFWwindow *currentWindow)
{
	window = currentWindow;
}

void InputManager::SetControllerIndex(unsigned int index)
{
	controllerIndex = index;
}

bool InputManager::IsControllerButtonPressed(unsigned int button)
{
	if (controllerIndex == NO_CONTROLLER_CONNTECTED)
		return false;

	bool buttonPressed = false;
	// Check if the input parameter is a face button, shoulder button, back/start button or joystick button
	if (button >= XBOX360_A && button < XBOX360_MAX_BUTTONS)
	{
		const unsigned char* buttons = glfwGetJoystickButtons(controllerIndex, &count);

		if (buttons[button] == GLFW_PRESS)
		{
			buttonPressed = true;

			// Check if the previous button state is false (button up)
			if (!previousControllerState.buttons[button])
			{
				currentControllerState.buttons[button] = buttonPressed;
			}
			else  // If the previous state is true (button down) then button can't be down agian
			{
				buttonPressed = false;
			}
		}
		else
		{
			// Button is not pressed so update the current state
			currentControllerState.buttons[button] = false;
		}

		// Update the previous face button state
		previousControllerState.buttons[button] = currentControllerState.buttons[button];
	}
	
	return buttonPressed;
}

bool InputManager::IsControllerButtonDown(unsigned int button)
{
	if (controllerIndex == NO_CONTROLLER_CONNTECTED)
		return false;

	bool buttonPressed = false;
	// Check if the input parameter is a face button, shoulder button, back/start button or joystick button
	if (button >= XBOX360_A && button < XBOX360_MAX_BUTTONS)
	{
		const unsigned char* buttons = glfwGetJoystickButtons(controllerIndex, &count);

		if (buttons[button] == GLFW_PRESS)
		{
			buttonPressed = true;
			currentControllerState.buttons[button] = buttonPressed;
		}
		else
		{
			// Button is not pressed so update the current state
			currentControllerState.buttons[button] = false;
		}
	}

	return buttonPressed;
}

Vector2 InputManager::GetLeftJoyStick()
{
	Vector2 leftThumbStick;

	if (controllerIndex == NO_CONTROLLER_CONNTECTED)
		return leftThumbStick;

	const float *axis = glfwGetJoystickAxes(controllerIndex, &count);
	leftThumbStick.x = axis[LEFT_STICK_X];
	leftThumbStick.y = axis[LEFT_STICK_Y];

	currentControllerState.leftThumbStick = leftThumbStick;

	return leftThumbStick;
}

Vector2 InputManager::GetRightJoyStick()
{
	Vector2 rightThumbStick;

	if (controllerIndex == NO_CONTROLLER_CONNTECTED)
		return rightThumbStick;

	const float *axis = glfwGetJoystickAxes(controllerIndex, &count);
	rightThumbStick.x = axis[RIGHT_STICK_X];
	rightThumbStick.y = axis[RIGHT_STICK_Y];

	currentControllerState.rightThumbStick = rightThumbStick;

	return rightThumbStick;
}

float InputManager::GetLeftTrigger()
{
	float leftTrigger = 0.0f;

	if (controllerIndex == NO_CONTROLLER_CONNTECTED)
		return leftTrigger;

	const float *axis = glfwGetJoystickAxes(controllerIndex, &count);
	leftTrigger = axis[TRIGGERS];

	currentControllerState.leftTrigger = leftTrigger;

	return leftTrigger;
}

float InputManager::GetRightTrigger()
{
	float rightTrigger = 0.0f;

	if (controllerIndex == NO_CONTROLLER_CONNTECTED)
		return rightTrigger;

	const float *axis = glfwGetJoystickAxes(controllerIndex, &count);
	rightTrigger = axis[TRIGGERS];

	currentControllerState.rightTrigger = rightTrigger;

	return rightTrigger;
}