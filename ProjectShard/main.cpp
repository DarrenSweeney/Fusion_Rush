#include <iostream>

#include "ResourceManager.h"
#include "InputManager.h"
#include "GameApplication.h"

#include <GL\gl3w.h>
#include <GLFW\glfw3.h>

//void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
//void mouse_callback(GLFWwindow *window, double xPos, double yPos);
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Camera camera(Vector3(0.0f, 3.0f, 3.0f));
GLfloat lastX, lastY;
bool keys[1024];
bool activeCamera;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

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
	//glfwSetKeyCallback(window, key_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetMouseButtonCallback(window, mouse_button_callback);

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

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	g_resourceMgr.LoadSceneShaders();
	g_resourceMgr.LoadSceneModels();
	g_resourceMgr.LoadSceneTextures();
	g_resourceMgr.PrintShaderTable();

	GameApplication gameApp;
	gameApp.Init();


	/*Sound sound;
	sound.Play2D();*/

	InputManager::GetInstance().SetWindow(window);

	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		camera.KeyboardMovement(keys, deltaTime);
		camera.ControllerMovement();

		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (InputManager::GetInstance().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
			activeCamera = true;
		else
			activeCamera = false;

		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gameApp.Update();
		gameApp.Render(camera);

		Vector2 cursorPos = InputManager::GetInstance().GetCursorPos();

		GLfloat xOffset = cursorPos.x - lastX;
		GLfloat yOffset = lastY - cursorPos.y;
		lastX = cursorPos.x;
		lastY = cursorPos.y;

		if (activeCamera)
			camera.MouseMovement(xOffset, yOffset);

		//g_debugDrawMgr.Submit(camera);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

#pragma region "User input"
//
//void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
//{
//	if (key >= 0 && key < 1024)
//	{
//		if (action == GLFW_PRESS)
//			keys[key] = true;
//		else if (action == GLFW_RELEASE)
//			keys[key] = false;
//	}
//}
//
//bool first_entered_window = true;
//void mouse_callback(GLFWwindow *window, double xPos, double yPos)
//{
//	if (first_entered_window)
//	{
//		first_entered_window = false;
//	}
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//
//}

#pragma endregion