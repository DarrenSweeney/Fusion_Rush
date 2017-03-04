#include <iostream>

#include <GameSparks/GS.h>
#include <GameSparks/IGSPlatform.h>
#include <GameSparks/generated/GSRequests.h>
#include <GameSparks/generated/GSMessages.h>

#include "./extra/usleep.h"
#include "sample_configuration.h"



/* this is a request of a custom event, which adds and remove an achievement for the player 
	
	Event Data:
		Short COde: GETACHIEVEMENT
		Name: Get Achievement
		Description: Add and remove an achievement to the player

		Properties:
			Name: Achievement Name
			Short Code: ACHIEVEMENTNAME
			Data Type: String
			Default Calc: Used in Script

	Cloud Code:
		
		var player = Spark.getPlayer();

		player.addAchievement(Spark.getData().ACHIEVEMENTNAME);
		player.removeAchievement(Spark.getData().ACHIEVEMENTNAME);

*/

class GetAchievementResponse : public GameSparks::Core::GSTypedResponse
{
public:
	GetAchievementResponse(const  GameSparks::Core::GSData& data)
		: GSTypedResponse(data)
	{

	}

	GetAchievementResponse(const GetAchievementResponse& other)
		: GSTypedResponse(other)
	{
	}
};

class GetAchievementRequest : public GameSparks::Core::GSTypedRequest < GetAchievementRequest, GetAchievementResponse >
{
public:
    GetAchievementRequest(GameSparks::Core::GS& gsInstance)
		: GSTypedRequest(gsInstance)
	{
		m_Request.AddString("eventKey", "GETACHIEVEMENT");
	}

	GetAchievementRequest& SetAchievementName(const gsstl::string& achievementName)
	{
		m_Request.AddString("ACHIEVEMENTNAME", achievementName);
		return *this;
	}
};

void GetAchievementRequest_Repsonse(GameSparks::Core::GS&, const GetAchievementResponse& response)
{
	std::cout << response.GetBaseData().GetJSON().c_str() << std::endl;
}



void ListAchievementsRequest_Response(GameSparks::Core::GS& gsInstance, const GameSparks::Api::Responses::ListAchievementsResponse& response)
{
	std::cout << response.GetBaseData().GetJSON().c_str() << std::endl;

	auto achievements = response.GetAchievements();

	for (gsstl::vector<GameSparks::Api::Types::Achievement>::iterator it = achievements.begin(); it != achievements.end(); ++it)
	{
		std::cout << it->GetName().GetValue().c_str() << std::endl;
	}

	// create and send an custom event which will add and remove an achievement
	GetAchievementRequest request(gsInstance);
	request.SetAchievementName("MYACHIEVEMENT");
	request.Send(GetAchievementRequest_Repsonse);

	
}

void AuthenticationRequest_Response(GameSparks::Core::GS& gsInstance, const GameSparks::Api::Responses::AuthenticationResponse& response)
{
	// when we login successully, we want to call a custom event
	if (response.GetHasErrors())
	{
		std::cout << "something went wrong during the authentication" << std::endl;
		std::cout << response.GetErrors().GetValue().GetJSON().c_str() << std::endl;
	}
	else
	{
		std::cout << "you successfully authenticated to GameSparks with your credentials" << std::endl;
		std::cout << "your displayname is " << response.GetBaseData().GetString("displayName").GetValue().c_str() << std::endl;

		// get all achievements for the player
		GameSparks::Api::Requests::ListAchievementsRequest request(gsInstance);
		request.Send(ListAchievementsRequest_Response);
	}

}

void GameSparksAvailable(GameSparks::Core::GS& gsInstance, bool available)
{
	std::cout << "GameSparks is " << (available ? "available" : "not available") << std::endl;
	
	if (available)
	{
		// login immediately when gamesparks is available

		GameSparks::Api::Requests::AuthenticationRequest request(gsInstance);
		request.SetUserName("abcdefgh");
		request.SetPassword("abcdefgh");
		request.Send(AuthenticationRequest_Response);
	}
}

void OnAchievementEarnedMessage(GameSparks::Core::GS&, const GameSparks::Api::Messages::AchievementEarnedMessage& message)
{
	std::cout << "Achievement earned " << message.GetAchievementName().GetValue().c_str() << std::endl;
}

int main(int argc, const char* argv[])
{
    (void)(argc); // unused
    (void)(argv); // unused

    using namespace GameSparks::Api::Messages;
    
    GameSparks::Core::GS gs;

	SampleConfiguration::NativePlatformDescription platform;
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


