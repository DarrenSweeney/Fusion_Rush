#include <iostream>

#include <GameSparks/GS.h>
#include <GameSparks/IGSPlatform.h>
#include <GameSparks/generated/GSRequests.h>
#include <GameSparks/generated/GSMessages.h>

#include <GameSparksRT/IRTSession.hpp>
#include <GameSparksRT/IRTSessionListener.hpp>
#include <GameSparksRT/RTData.hpp>

#include "./extra/usleep.h"
#include "sample_configuration.h"
#include <memory> // for std::unique_ptr
#include <ctime> // for initializing rand()

/*
	This sample illustrates some of the features of GameSparks RT.
	For this to work, you need to create a match with a short code of "TestMatch".
*/



void MatchmakingRequest_Response(GameSparks::Core::GS&, const GameSparks::Api::Responses::MatchmakingResponse& response)
{
	if (response.GetHasErrors())
	{
		std::cerr << "!!! Error in Response:" << response.GetErrors().GetValue().GetJSON() << std::endl;
	}
}

void SendMatchmakingRequest(GameSparks::Core::GS& gs)
{
	GameSparks::Api::Requests::MatchmakingRequest makeMatch(gs);
	makeMatch.SetSkill(1);
	makeMatch.SetMatchShortCode("TestMatch");
	makeMatch.Send(MatchmakingRequest_Response);
}

void AuthenticationRequest_Response(GameSparks::Core::GS& gsInstance, const GameSparks::Api::Responses::AuthenticationResponse& response)
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

		// OK, we're authenticated, send out the initial MatchmakingRequest ...
		SendMatchmakingRequest(gsInstance);
	}
}

void GameSparksAvailable(GameSparks::Core::GS& gsInstance, bool available)
{
	std::cout << "GameSparks is " << (available ? "available" : "not available") << std::endl;

	if (available)
	{
		// send a device authentication request with a random device id.
		// this is done so that you can start two instances on the same machine.
		// In a production title, you'd use IGSPlatform::GetDeviceId() instead.
		GameSparks::Api::Requests::DeviceAuthenticationRequest authRequest(gsInstance);	
		std::srand(std::time(nullptr));
		auto rrr = std::rand();
		authRequest.SetDeviceId(std::to_string(rrr)); // generate a random device id (for easy testing)
		authRequest.SetDeviceOS("W8");
		authRequest.Send(AuthenticationRequest_Response);
	}
}


class GameSession : GameSparks::RT::IRTSessionListener
{
	public:
		std::unique_ptr<GameSparks::RT::IRTSession> Session;

		GameSession(const std::string& connectToken, const std::string& host, const std::string& port)
		{
			Session.reset(GameSparks::RT::GameSparksRT
				::SessionBuilder()
				.SetConnectToken(connectToken)
				.SetHost(host)
				.SetPort(port)
				.SetListener(this)
				.Build());

			Session->Start();
		}

		void OnPlayerConnect(int peerId) override
		{
			std::clog << " OnPlayerConnect:" << peerId << std::endl;
		}

		void OnPlayerDisconnect(int peerId) override
		{
			std::clog << " OnPlayerDisconnect:" << peerId << std::endl;
		}

		void OnReady(bool ready) override
		{
			std::clog << " OnReady:" << std::boolalpha << ready << std::endl;
		}

		void OnPacket(const GameSparks::RT::RTPacket& packet) override
		{
			std::clog << "OnPacket: " << packet.Data << std::endl;
		}
};


int main(int argc, const char* argv[])
{
    (void)(argc); // unused
    (void)(argv); // unused

    using namespace GameSparks::Core;
	using namespace GameSparks::Api::Messages;

    GameSparks::Core::GS gs;
    
    SampleConfiguration::NativePlatformDescription platform;
	gs.Initialise(&platform);

	gs.GameSparksAvailable = GameSparksAvailable;

	// this will hold out GameSession once we have foud a match
	std::unique_ptr<GameSession> gameSession;

	// these message handlers are called after a MatchmakingRequest has been sent (see SendMatchmakingRequest)

	// MatchFoundMessage
	gs.SetMessageListener<MatchFoundMessage>([&](GS& gs, const MatchFoundMessage& message) {
		std::clog << "MatchFoundMessage: " << message.GetJSONString() << std::endl;
		gameSession.reset(new GameSession(
			message.GetAccessToken().GetValue(),
			message.GetHost().GetValue(),
			std::to_string(message.GetPort().GetValue())
		));
	});

	// MatchNotFoundMessage
	gs.SetMessageListener<MatchNotFoundMessage>([&](GS& gs, const MatchNotFoundMessage& message) {
		std::clog << "MatchNotFoundMessage: " << message.GetJSONString() << std::endl;
		SendMatchmakingRequest(gs); // try again
	});

	// MatchUpdatedMessage
	gs.SetMessageListener<MatchUpdatedMessage>([&](GS& gs, const MatchUpdatedMessage& message) {
		std::clog << "MatchUpdatedMessage: " << message.GetJSONString() << std::endl;
	});

	int cyclesLeft = 200000;
	while (cyclesLeft-- > 0)
	{
		// deltaTime has to be provided in seconds
		gs.Update(0.1f);

		if (gameSession)
		{
			gameSession->Session->Update();
			GameSparks::RT::RTData data;
			data.SetInt(1, cyclesLeft); // do something useful here
			gameSession->Session->SendRTData(1, GameSparks::RT::GameSparksRT::DeliveryIntent::RELIABLE, data, {});
		}

		usleep(100000);
	}

	gs.ShutDown();
}
