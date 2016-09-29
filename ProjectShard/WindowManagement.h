#ifndef WINDOW_MANAGEMENT_H
#define WINDOW_MANAGEMETN_H

#include <iostream>
#include <GL\gl3w.h>
#include <GLFW\glfw3.h>

// Sets up OpenGL context and GLFW window managment
class WindowManagement
{
private:
	GLFWwindow *window;

public:
	GLFWwindow *GetWindow();
	bool CloseState();
	void SetCloseState(int state);
	void StartUp();
	void ShutDown();
};

#endif