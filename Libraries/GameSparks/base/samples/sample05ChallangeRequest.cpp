#include <iostream>

#include <GameSparks/GS.h>
#include <GameSparks/IGSPlatform.h>
#include <GameSparks/generated/GSRequests.h>
#include <GameSparks/generated/GSMessages.h>

#include "./extra/usleep.h"
#include "sample_configuration.h"

using namespace GameSparks::Core;
using namespace GameSparks::Api::Messages;
using namespace GameSparks::Api::Responses;
using namespace GameSparks::Api::Requests;

void WithdrawChallengeRequest_Response(GS&, const WithdrawChallengeResponse& response)
{
	std::cout << "withdraw challnage: " << std::endl;
	std::cout << response.GetJSONString().c_str() << std::endl;
}

void GetChallengeRequest_Response(GS& gsInstance, const GetChallengeResponse& response)
{
	std::cout << "get challange data: " << std::endl;
	std::cout << response.GetChallenge().GetJSONString().c_str() << std::endl;

	WithdrawChallengeRequest request(gsInstance);
	request.SetChallengeInstanceId(response.GetChallenge().GetChallengeId().GetValue());
	request.SetMessage("automated decline");
	request.Send(WithdrawChallengeRequest_Response);
}

void CreateChallengeRequest_Response(GS& gsInstance, const GameSparks::Api::Responses::CreateChallengeResponse& response)
{
	std::cout << "challange response: " << response.GetJSONString().c_str() << std::endl;

	GetChallengeRequest request(gsInstance);
	request.SetChallengeInstanceId(response.GetBaseData().GetString("challengeInstanceId").GetValue());
	request.Send(GetChallengeRequest_Response);
}

void AuthenticationRequest_Response(GS& gsInstance, const GameSparks::Api::Responses::AuthenticationResponse& response)
{
	// when we login successfully, we want to call a custom event
	if (response.GetHasErrors())
	{
		std::cout << "something went wrong during the authentication" << std::endl;
		std::cout << response.GetErrors().GetValue().GetJSON().c_str() << std::endl;
	}
	else
	{
		std::cout << "you successfully authenticated to GameSparks with your credentials" << std::endl;
		std::cout << "your displayname is " << response.GetBaseData().GetString("displayName").GetValue().c_str() << std::endl;

		GSDateTime now = GSDateTime::Now();

		GameSparks::Api::Requests::CreateChallengeRequest challangeRequest(gsInstance);
		challangeRequest.SetAccessType("PUBLIC");
		challangeRequest.SetChallengeMessage("Ultimate Challange");
		challangeRequest.SetChallengeShortCode("ULTIMATECHALLANGE");
		challangeRequest.SetEndTime(now.AddHours(2).ToGMTime());
		challangeRequest.SetExpiryTime(now.AddMinutes(5).ToGMTime());
		challangeRequest.SetMaxPlayers(5);
		challangeRequest.SetMaxAttempts(5);
		challangeRequest.SetMinPlayers(2);
		challangeRequest.SetSilent(false);
		challangeRequest.SetStartTime(now.AddHours(1).ToGMTime());

		challangeRequest.Send(CreateChallengeRequest_Response);
	}
}

void RegistrationRequest_Response(GS& gsInstance, const GameSparks::Api::Responses::RegistrationResponse& response)
{
	if (response.GetHasErrors() && response.GetErrors().GetValue().GetString("USERNAME").GetValue() != "TAKEN")
	{
		std::cout << "something went wrong during the registration" << std::endl;
		std::cout << response.GetErrors().GetValue().GetJSON().c_str() << std::endl;
	}
	else
	{
		// login immediately when gamesparks is available
		GameSparks::Api::Requests::AuthenticationRequest request(gsInstance);
		request.SetUserName("abcdefgh");
		request.SetPassword("abcdefgh");
		request.Send(AuthenticationRequest_Response);
	}
}

void GameSparksAvailable(GS& gsInstance, bool available)
{
	std::cout << "GameSparks is " << (available ? "available" : "not available") << std::endl;
	
	if (available)
	{
		{
			GameSparks::Api::Requests::RegistrationRequest req(gsInstance);
			req.SetUserName("abcdefgh");
			req.SetPassword("abcdefgh");
			req.SetDisplayName("SuperPlayer007");
			req.Send(RegistrationRequest_Response);
		}
	}
}

void OnAchievementEarnedMessage(GS&, const GameSparks::Api::Messages::AchievementEarnedMessage& message)
{
	std::cout << "Achievement earned " << message.GetAchievementName().GetValue().c_str() << std::endl;
}

int main(int argc, const char* argv[])
{
    (void)(argc); // unused
    (void)(argv); // unused

    SampleConfiguration::NativePlatformDescription platform;
    GameSparks::Core::GS gs;
    
	gs.Initialise(&platform);

	// this event handler will login the user (see above)
	gs.GameSparksAvailable = GameSparksAvailable;

	gs.SetMessageListener<AchievementEarnedMessage>(OnAchievementEarnedMessage);

	int cyclesLeft = 200000;
	while (cyclesLeft-- > 0)
	{
		// deltaTime has to be provided in seconds
		gs.Update(0.1f);
		usleep(100000);
	}

	gs.ShutDown();
}


