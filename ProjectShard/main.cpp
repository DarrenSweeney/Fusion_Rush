#include <iostream>

#include "Core\ResourceManager.h"
#include "Input\InputManager.h"
#include "Game\GameApplication.h"
#include "Audio\SoundEngine.h"
#include "Platform\WindowManagement.h"

// Testing out GameSparks SDK
#include <GameSparks\GS.h>
#include <GameSparks\IGSPlatform.h>
#include <GameSparks\generated/GSRequests.h>
#include <GameSparks\generated\GSResponses.h>
#include "GameSparksConfiguration.h"
#include "GameSparks\GSOptional.h"

using namespace GameSparks::Core;
using namespace GameSparks::Api::Responses;
using namespace GameSparks::Api::Requests;
using namespace GameSparks::Optional;
using namespace GameSparks::Api::Types;

gsstl::vector<LeaderboardData> givemedata;

void RegistrationRequest_Response(GS& gsInstance, const RegistrationResponse& response) 
{
	t_StringOptional authToken = response.GetAuthToken();
	t_StringOptional displayName = response.GetDisplayName();
	t_BoolOptional newPlayer = response.GetNewPlayer();
	GSData::t_Optional scriptData = response.GetScriptData();
	GameSparks::Api::Types::Player switchSummary = response.GetSwitchSummary();
	t_StringOptional userId = response.GetUserId();
}

void LeaderboardDataRequest_Response(GS& gsInstance, const LeaderboardDataResponse& response) 
{
	gsstl::vector<LeaderboardData> data = response.GetData();
	givemedata = response.GetFirst();
	gsstl::vector<LeaderboardData> last = response.GetLast();
	t_StringOptional leaderboardShortCode = response.GetLeaderboardShortCode();
}

void AuthenticationRequest_Response(GameSparks::Core::GS&, const GameSparks::Api::Responses::AuthenticationResponse& response)
{
	if (response.GetHasErrors())
	{
		std::cout << "something went wrong during the authentication" << std::endl;
		std::cout << response.GetErrors().GetValue().GetJSON().c_str() << std::endl;
	}
	else
	{
		std::cout << "you successfully authenticated to GameSparks with your credentials" << std::endl;
		std::cout << "your displayname is " << response.GetBaseData().GetString("displayName").GetValue().c_str() << std::endl;
	}
}

void GameSparksAvailable(GameSparks::Core::GS& gsInstance, bool available)
{
	std::cout << "\nGameSparks is " << (available ? "available" : "not available") << std::endl;

	if (available)
	{
		// try with wrong credentials
		GameSparks::Api::Requests::AuthenticationRequest requestWrong(gsInstance);
		requestWrong.SetUserName("TOTALLYWRONGUSER");
		requestWrong.SetPassword("TOTALLYWRONGPASSWORD");
		requestWrong.Send(AuthenticationRequest_Response);

		// try with right credentials
		GameSparks::Api::Requests::AuthenticationRequest requestRight(gsInstance);
		requestRight.SetUserName("SpyroTheDragon");
		requestRight.SetPassword("password");
		requestRight.Send(AuthenticationRequest_Response);
	}
}

int main(int argc, char* argv[])
{
	WindowManagement window;
	window.StartUp();

	std::cout << "--- Initialise GameSparks ---" << std::endl;
	GS gs;
	GameSparksConfiguration::NativePlatformDescription platform;
	gsstl::string message;
	platform.DebugMsg(message);
	gs.Initialise(&platform);
	gs.GameSparksAvailable = GameSparksAvailable;

	RegistrationRequest registrationRequest(gs);
	registrationRequest.SetDisplayName("DarrenSweeney");
	registrationRequest.SetPassword("password");
	registrationRequest.SetUserName("SpyroTheDragon");
	registrationRequest.Send(RegistrationRequest_Response);

	// Responce parameters
	LeaderboardDataRequest request(gs);
	request.SetEntryCount(5);
	request.SetLeaderboardShortCode("Race_Times");
	request.Send(LeaderboardDataRequest_Response);
	std::cout << "--- End GameSparks ---" << std::endl;

	SoundEngine soundEngine;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	std::cout << "\n--- Start ResourceMgr ---" << std::endl;
	g_resourceMgr.LoadSceneShaders();
	g_resourceMgr.LoadSceneModels();
	g_resourceMgr.LoadSceneTextures();
	g_resourceMgr.PrintShaderTable();
	std::cout << "--- End ResourceMgr ---\n" << std::endl;

	GameApplication gameApp;
	gameApp.Init();

	InputManager::GetInstance().SetWindowContext(window.GetWindow());
	bool polygonMode = false;

	while (!window.CloseState())
	{
		gs.Update(glfwGetTime());

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