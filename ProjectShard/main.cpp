#include <iostream>

#include "Core\ResourceManager.h"
#include "Input\InputManager.h"
#include "Game\GameApplication.h"
#include "Audio\SoundEngine.h"
#include "Platform\WindowManagement.h"

// Testing out GameSparks SDK
#include <GameSparks/GS.h>
#include <GameSparks/IGSPlatform.h>
#include <GameSparks/generated/GSRequests.h>
#include <GameSparks/generated\GSResponses.h>
#include "GameSparksConfiguration.h"
#include "GameSparks\GSOptional.h"

using namespace GameSparks::Core;
using namespace GameSparks::Api::Responses;
using namespace GameSparks::Api::Requests;
using namespace GameSparks::Optional;
using namespace GameSparks::Api::Types;

void LeaderboardDataRequest_Response(GS& gsInstance, const LeaderboardDataResponse& response) 
{
	t_StringOptional challengeInstanceId = response.GetChallengeInstanceId();
	gsstl:vector<LeaderboardData> data = response.GetData();
	gsstl::vector<LeaderboardData> first = response.GetFirst();
	gsstl::vector<LeaderboardData> last = response.GetLast();
	t_StringOptional leaderboardShortCode = response.GetLeaderboardShortCode();
	GSData::t_Optional scriptData = response.GetScriptData();
}

int main(int argc, char* argv[])
{
	WindowManagement window;
	window.StartUp();

	GS gs;
	GameSparksConfiguration::NativePlatformDescription platform;
	gsstl::string message;
	platform.DebugMsg(message);
	gs.Initialise(&platform);

	LeaderboardDataRequest request(gs);
	long _entryCount = 10;
	// Request parameters
	request.SetEntryCount(_entryCount);
	request.Send(LeaderboardDataRequest_Response);

	// Responce parameters
	//LeaderboardDataResponse responce(,);

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