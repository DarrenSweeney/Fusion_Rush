#ifndef WINDOW_MANAGEMENT_H
#define WINDOW_MANAGEMETN_H

#include <iostream>
#include <GL\gl3w.h>
#include <GLFW\glfw3.h>
#include "..\Input\InputManager.h"

// Sets up OpenGL context and GLFW window managment
class WindowManagement
{
private:
	GLFWwindow *window;
	int width, height;

public:
	GLFWwindow *GetWindow();
	int GetWidth();
	int GetHeight();
	bool CloseState();
	void SetCloseState(int state);
	void GetFrameBufferSize(int *width, int *height);
	void PollEvents();
	void StartUp();
	void UpdateViewport();
	void SwapBuffers();
	void ShutDown();
};

#endif