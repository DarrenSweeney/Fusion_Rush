#include "WindowManagement.h"

#define FULLSCREEN false

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void window_size_callback(GLFWwindow* window, int width, int height);
void character_callback(GLFWwindow* window, unsigned int codepoint);
bool WindowManagement::windowResized;

GLFWwindow *WindowManagement::GetWindow()
{
	return window;
}

int WindowManagement::GetWidth()
{
	return width;
}

int WindowManagement::GetHeight()
{
	return height;
}

bool WindowManagement::GetWindowResized()
{
	return windowResized;
}

bool WindowManagement::CloseState()
{
	if (glfwWindowShouldClose(window))
		return true;
	else
		return false;
}

void WindowManagement::SetCloseState(int state)
{
	glfwSetWindowShouldClose(window, state);
}

void WindowManagement::GetFrameBufferSize(int *width, int *height)
{
	glfwGetFramebufferSize(window, width, height);
}

void WindowManagement::PollEvents()
{
	glfwPollEvents();
}

void WindowManagement::StartUp()
{
	std::cout << "----- FUSION RUSH -----" << std::endl;

	if (!glfwInit())
	{
		std::cout << "Failed to initialize OpenGL" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Get the desktop resolution.
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
	width = vidMode->width;		// 1600
	height = vidMode->height;	// 800

	window = glfwCreateWindow(width, height, "Project Shard", FULLSCREEN ? glfwGetPrimaryMonitor() : NULL, NULL);
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetCharCallback(window, character_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	if (!window)
	{
		glfwTerminate();
		std::cout << "GLFW terminated" << std::endl;
		return;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit())
	{
		std::cout << "Failed to initialize OpenGL" << std::endl;
		return;
	}

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	glfwGetFramebufferSize(window, &width, &height);
	glfwSetWindowPos(window, 0, 0);
	glViewport(0, 0, width, height);
}

void WindowManagement::UpdateViewport()
{
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void WindowManagement::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void WindowManagement::ShutDown()
{
	glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < InputManager::GetInstance().MAX_KEYS)
	{
		if (GLFW_PRESS == action)
		{
			if (!InputManager::GetInstance().keys_locked[key])
			{
				InputManager::GetInstance().keys_down[key] = true;
			}
		}
		if (GLFW_RELEASE == action)
		{
			InputManager::GetInstance().keys_down[key] = false;
			InputManager::GetInstance().keys_locked[key] = false;
		}
	}
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	WindowManagement::windowResized = true;
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	char key = codepoint;

	InputManager::GetInstance().keyInput.push_back(key);
	InputManager::GetInstance().charaterKeyPressed = true;
}