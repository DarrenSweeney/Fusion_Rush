#include <iostream>

#include "TestPlayArea.h"
#include "Camera.h"

#include "HashID.h"

#include <GL\gl3w.h>
#include <GLFW\glfw3.h>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Camera camera(Vector3(0.0f, 3.0f, 3.0f));
GLfloat lastX, lastY;
bool keys[1024];
bool activeCamera;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

#define SID( string ) string
//typedef sid int; // 32bit in my case

constexpr const unsigned long long StringIdHashConcat(unsigned long long base, const char *str)
{
	return (*str) ? (StringIdHashConcat((base ^ *str) * 0x100000001b3, str + 1)) : base;
}

constexpr const unsigned long long StringIdHash(const char *str)
{
	return StringIdHashConcat(0xcbf29ce484222325, str);
}

int main(int argc, char* argv[])
{
	std::cout << "DARREN_SWEENEY::Project Shard..." << std::endl;

	if (!glfwInit())
	{
		printf("Failed to inialize opengl");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(900, 600, "Project Shard", NULL, NULL);

	// GLFW input callbacks.
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit())
	{
		printf("Failed to inialize opengl");
		return -1;
	}

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	TestPlayArea testPlayArea;
	testPlayArea.InitalizeScene();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	const char* name = "Darren";
	int size = sizeof(name);
	std::string nameString = "Darren";
	size = sizeof(name);
	unsigned long nameHash = StringIdHash(name);
	size = sizeof(nameHash);

	const char* name2 = "Darren";
	unsigned long nameHash2 = StringIdHash(name2);

	const HashID sid0 = SID("Darren");
	const HashID sid1 = SID("nerraD");
	const HashID sid3 = SID("Darren");

	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		camera.KeyboardMovement(keys, deltaTime);
		camera.ControllerMovement();

		testPlayArea.UpdateScene();

		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		testPlayArea.RenderScene(camera);

		//g_debugDrawMgr.Submit(camera);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}


#pragma region "User input"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

bool first_entered_window = true;
void mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
	if (first_entered_window)
	{
		lastX = xPos;
		lastY = yPos;
		first_entered_window = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	if (activeCamera)
		camera.MouseMovement(xOffset, yOffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		activeCamera = true;
	else
		activeCamera = false;
}

#pragma endregion