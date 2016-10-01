#include <iostream>

#include "ResourceManager.h"
#include "InputManager.h"
#include "GameApplication.h"
#include "EngineComponents.h"
#include "WindowManagement.h"

int main(int argc, char* argv[])
{
	WindowManagement window;
	window.StartUp();

	EngineComponents engineComp;

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

		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_ESCAPE))
			window.SetCloseState(GL_TRUE);

		gameApp.Update(deltaTime);
		gameApp.Render();

		window.SwapBuffers();
	}

	window.ShutDown();
	return 0;
}