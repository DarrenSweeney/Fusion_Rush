#include "WindowManagement.h"

GLFWwindow *WindowManagement::GetWindow()
{
	return window;
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

void WindowManagement::StartUp()
{
	std::cout << "DARREN_SWEENEY::Project Shard..." << std::endl;

	if (!glfwInit())
	{
		std::cout << "Failed to inialize opengl" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(900, 600, "Project Shard", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		std::cout << "GLFW terminated" << std::endl;
		return;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit())
	{
		std::cout << "Failed to inialize opengl" << std::endl;
		return;
	}

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void WindowManagement::ShutDown()
{
	glfwTerminate();
}