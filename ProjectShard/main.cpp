#include <iostream>
#include <GLFW\glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
bool windowOpened = false;

int main(int argc, char* argv[])
{
	std::cout << "DARREN_SWEENEY::Project Shard..." << std::endl;

	GLFWwindow *window;

	if (!glfwInit())
		return -1;
	
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	glfwSetKeyCallback(window, key_callback);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	else
		windowOpened = true;

	glfwMakeContextCurrent(window);
	
	while (windowOpened)
	{
	
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
	
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		windowOpened = false;
}