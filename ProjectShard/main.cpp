#include <iostream>

#include "Core\ResourceManager.h"
#include "Input\InputManager.h"
#include "Game\GameApplication.h"
#include "Audio\SoundEngine.h"
#include "Platform\WindowManagement.h"

// Testing out GameSparks SDK
#include <GameSparks/GS.h>
#include <GameSparks/IGSPlatform.h>

#include "GameSparksConfiguration.h"

using namespace GameSparks::Core;

int main(int argc, char* argv[])
{
	WindowManagement window;
	window.StartUp();

	GS gs;
	GameSparksConfiguration::NativePlatformDescription platform;
	gsstl::string message;
	platform.DebugMsg(message);
	gs.Initialise(&platform);

	SoundEngine soundEngine;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	g_resourceMgr.LoadSceneShaders();
	g_resourceMgr.LoadSceneModels();
	g_resourceMgr.LoadSceneTextures();
	g_resourceMgr.PrintShaderTable();

	GameApplication gameApp;
	gameApp.Init();

	InputManager::GetInstance().SetWindowContext(window.GetWindow());
	bool polygonMode = false;

	while (!window.CloseState())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_F1))
			polygonMode = !polygonMode;

		glPolygonMode(GL_FRONT_AND_BACK, polygonMode ? GL_LINE : GL_FILL);

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

	gs.ShutDown();
	window.ShutDown();
	return 0;
}