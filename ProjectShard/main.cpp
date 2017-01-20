#include <iostream>

#include "Platform\WindowManagement.h"
#include "Input\InputManager.h"
#include "Game\GameApplication.h"

int main(int argc, char* argv[])
{
	WindowManagement window;
	window.StartUp();

	SoundEngine soundEngine;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	InputManager::GetInstance().SetWindowContext(window.GetWindow());

	std::cout << "\n--- Start ResourceMgr ---" << std::endl;
	g_resourceMgr.LoadSceneShaders();
	g_resourceMgr.LoadSceneModels();
	g_resourceMgr.LoadSceneTextures();
	std::cout << "--- End ResourceMgr ---\n" << std::endl;

	GameApplication gameApp(window.GetWidth(), window.GetHeight());
	gameApp.Init();

	while (!window.CloseState())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		window.PollEvents();
		window.UpdateViewport();

		if(glfwJoystickPresent(CONTROLLER_ONE))
			InputManager::GetInstance().SetControllerIndex(CONTROLLER_ONE);
		else
			InputManager::GetInstance().SetControllerIndex(NO_CONTROLLER_CONNTECTED);

		if (gameApp.GetCloseState())
			window.SetCloseState(GL_TRUE);

		// Update the screen size
		glfwGetWindowSize(window.GetWindow(), &gameApp.screenWidth, &gameApp.screenHeight);

		gameApp.Update(deltaTime);
		gameApp.Render(window.windowResized);
		window.windowResized = false;

		window.SwapBuffers();
	}

	window.ShutDown();
	return 0;
}