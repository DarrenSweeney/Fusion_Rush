#include "WindowManagement.h"

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
	std::cout << "DARREN_SWEENEY::Project Shard..." << std::endl;

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
	width = vidMode->width;
	height = vidMode->height;

	window = glfwCreateWindow(width, height, "Project Shard", NULL, NULL);

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