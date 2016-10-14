#include <iostream>

#include "Core\ResourceManager.h"
#include "Input\InputManager.h"
#include "Game\GameApplication.h"
#include "Audio\SoundEngine.h"
#include "Platform\WindowManagement.h"

int main(int argc, char* argv[])
{
	WindowManagement window;
	window.StartUp();

	SoundEngine soundEngine;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	g_resourceMgr.LoadSceneShaders();
	g_resourceMgr.LoadSceneModels();
	g_resourceMgr.LoadSceneTextures();
	g_resourceMgr.PrintShaderTable();

	GameApplication gameApp;
	gameApp.Init();

	InputManager::GetInstance().SetWindow(window.GetWindow());

	int num = 0;
	int *ptr_num = &num;
	int num_1 = *ptr_num;
	int num_2 = *ptr_num;
	num_1 = 10;
	num_2 = 15;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!window.CloseState())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Set frame time
		// TODO(Darren): May create a time class with limited frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		window.PollEvents();
		window.UpdateViewport();

		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_ESCAPE))
			window.SetCloseState(GL_TRUE);

		gameApp.Update(deltaTime);
		gameApp.Render(window.GetWidth(), window.GetHeight());

		window.SwapBuffers();
	}

	window.ShutDown();
	return 0;
}