#include "InputManager.h"

InputManager::InputManager() { }

InputManager &InputManager::GetInstance()
{
	static InputManager *instance = new InputManager();
	return *instance;
}

bool InputManager::IsKeyPressed(int key)
{
	int state = glfwGetKey(window, key);

	if (state == GLFW_PRESS)
		return true;
	else
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

void InputManager::SetWindow(GLFWwindow *currentWindow)
{
	window = currentWindow;
}

bool InputManager::IsJoyStickPresent(int joystick)
{
	int present = glfwJoystickPresent(joystick);

	return present == 1 ? true : false;
}

const float *InputManager::GetJoyStickAxis(int joystick)
{
	const float *axis = NULL;

	if (IsJoyStickPresent(joystick))
	{
		axis = glfwGetJoystickAxes(joystick, &count);
	}
	                                                                              
	return axis;
}

const unsigned char *InputManager::GetJoyStickButtons(int joystick)
{
	const unsigned char* buttons = NULL;

	if (IsJoyStickPresent(joystick))
	{
		buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
	}

	return buttons;
}