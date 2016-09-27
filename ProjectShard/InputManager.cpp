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