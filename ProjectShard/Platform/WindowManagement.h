#ifndef WINDOW_MANAGEMENT_H
#define WINDOW_MANAGEMENT_H

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
	static bool windowResized;
	int GetWidth();
	int GetHeight();
	bool GetWindowResized();
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