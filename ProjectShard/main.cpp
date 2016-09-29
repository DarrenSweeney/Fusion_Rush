#include <iostream>

#include "ResourceManager.h"
#include "InputManager.h"
#include "GameApplication.h"

#include "WindowManagement.h"

int main(int argc, char* argv[])
{
	WindowManagement window;
	window.StartUp();

	Camera camera(Vector3(0.0f, 3.0f, 3.0f));
	GLfloat lastX = 0.0f;
	GLfloat lastY = 0.0f;
	bool activeCamera;
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	g_resourceMgr.LoadSceneShaders();
	g_resourceMgr.LoadSceneModels();
	g_resourceMgr.LoadSceneTextures();
	g_resourceMgr.PrintShaderTable();

	GameApplication gameApp;
	gameApp.Init();

	InputManager::GetInstance().SetWindow(window.GetWindow());

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!window.CloseState())
	{
		// Set frame time
		// TODO(Darren): May create a time class with limited frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		window.PollEvents();
		camera.KeyboardMovement(deltaTime);
		camera.ControllerMovement();

		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_ESCAPE))
			window.SetCloseState(GL_TRUE);

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

		window.SwapBuffers();
	}

	window.ShutDown();
	return 0;
}