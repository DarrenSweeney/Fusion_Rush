#include <iostream>

#include <GameSparks/GS.h>
#include <GameSparks/IGSPlatform.h>
#include <GameSparks/generated/GSRequests.h>

#include "./extra/usleep.h"
#include "sample_configuration.h"

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
	std::cout << "GameSparks is " << (available ? "available" : "not available") << std::endl;

	if (available)
	{
		// try with wrong credentials
		GameSparks::Api::Requests::AuthenticationRequest requestWrong(gsInstance);
		requestWrong.SetUserName("TOTALLYWRONGUSER");
		requestWrong.SetPassword("TOTALLYWRONGPASSWORD");
		requestWrong.Send(AuthenticationRequest_Response);

		// try with right credentials
		GameSparks::Api::Requests::AuthenticationRequest requestRight(gsInstance);
		requestRight.SetUserName("abcdefgh");
		requestRight.SetPassword("abcdefgh");
		requestRight.Send(AuthenticationRequest_Response);
	}
}

int main(int argc, const char* argv[])
{
    (void)(argc); // unused
    (void)(argv); // unused

    using namespace GameSparks::Core;

    GameSparks::Core::GS gs;
    
    SampleConfiguration::NativePlatformDescription platform;
	gs.Initialise(&platform);

	gs.GameSparksAvailable = GameSparksAvailable;

	int cyclesLeft = 200000;
	while (cyclesLeft-- > 0)
	{
		// deltaTime has to be provided in seconds
		gs.Update(0.1f);
		usleep(100000);
	}

	gs.ShutDown();
}
