#include <iostream>

#include "Platform\WindowManagement.h"
#include "Input\InputManager.h"
#include "Game\GameApplication.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

#include <iostream> // must be included before hack.h as SAL annotations
#include <iomanip>  // collide with GCC's standard library implmentation

// plus a few pretend types

#include "urlmon.h" // copied into project folder (from Windows SDK)
// along with the import library and an empty "msxml.h" file

#include <wininet.h> // MinGW does provide this (needed for DeleteUrlCacheEntry)

using namespace std;

#ifdef _UNICODE
#define tcout wcout
#else
#define tcout cout
#endif


int main(int argc, char* argv[])
{
	const TCHAR url[] = _T("https://gamesparksbetabinaries.blob.core.windows.net/game-303539/1485189293188/Race_Seed.txt?sig=9bnQBu06Ms5%2BacMayOgAHfIdZU%2B4I3t%2BkIsxNrTPU6c%3D&st=2017-01-23T21%3A14%3A10Z&se=2017-01-23T21%3A29%3A10Z&sv=2015-04-05&sp=r&sr=b&gsstage=preview");
	const TCHAR filePath[] = _T("Race_Seed.txt");

	tcout << _T("Downloading   : ") << url << endl;
	tcout << _T("To local file : ") << filePath << endl;

	// invalidate cache, so file is always downloaded from web site
	// (if not called, the file will be retieved from the cache if
	// it's already been downloaded.)
	DeleteUrlCacheEntry(url);

	HRESULT hr = URLDownloadToFile(
		NULL,   // A pointer to the controlling IUnknown interface (not needed here)
		url,
		filePath,
		0,      // Reserved. Must be set to 0.
		NULL); // status callback interface (not needed for basic use)
	if (SUCCEEDED(hr))
	{
		tcout << _T("Downloaded OK") << endl;
	}
	else
	{
		tcout << _T("An error occured : error code = 0x") << hex << hr << endl;
	}

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

		/*if(glfwJoystickPresent(CONTROLLER_ONE))
			InputManager::GetInstance().SetControllerIndex(CONTROLLER_ONE);
		else
			InputManager::GetInstance().SetControllerIndex(NO_CONTROLLER_CONNTECTED);*/

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