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
	//InputManager::GetInstance().SetControllerIndex(CONTROLLER_ONE);

	std::cout << "\n--- Start ResourceMgr ---" << std::endl;
	g_resourceMgr.LoadSceneShaders();
	g_resourceMgr.LoadSceneModels();
	g_resourceMgr.LoadSceneTextures();
	std::cout << "--- End ResourceMgr ---\n" << std::endl;

	GameApplication gameApp(window.GetWidth(), window.GetHeight());
	gameApp.Init();

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