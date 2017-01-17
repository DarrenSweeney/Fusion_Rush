#include "GameSparksInfo.h"

void AuthenticationRequest_Response(GameSparks::Core::GS&, const GameSparks::Api::Responses::AuthenticationResponse& response);
void RegistrationRequest_Response(GS& gsInstance, const GameSparks::Api::Responses::RegistrationResponse& response);
void LeaderboardDataRequest_Response(GS& gsInstance, const LeaderboardDataResponse& response);
void GameSparksAvailable(GameSparks::Core::GS& gsInstance, bool available);
void AroundMeLeaderboardRequest_Response(GS& gsInstance, const AroundMeLeaderboardResponse& response);

std::vector<LeaderboardEntry> GameSparksInfo::leaderboardEntry;
std::string GameSparksInfo::username, GameSparksInfo::password;
bool GameSparksInfo::loginSuccessful;
bool GameSparksInfo::registerAccount;
bool GameSparksInfo::signInAccount;
bool GameSparksInfo::available;
CurrentPlayer GameSparksInfo::currentPlayer;

GameSparksInfo::GameSparksInfo()
{
	InitGS();
}

void GameSparksInfo::InitGS()
{
	std::cout << "--- Initialise GameSparks ---" << std::endl;
	platform.DebugMsg(message);
	gs.Initialise(&platform);
	gs.GameSparksAvailable = GameSparksAvailable;
	std::cout << "--- End GameSparks ---" << std::endl;
}

GameSparksInfo::~GameSparksInfo()
{
	gs.ShutDown();
}

void GameSparksInfo::Update()
{
	gs.Update(0.1f);
}

bool GameSparksInfo::GetStatus()
{
	return available;
}

void AuthenticationRequest_Response(GameSparks::Core::GS&, const GameSparks::Api::Responses::AuthenticationResponse& response)
{
	if (response.GetHasErrors())
	{
		GameSparksInfo::loginSuccessful = false;
		std::cout << "something went wrong during the authentication" << std::endl;
		std::cout << response.GetErrors().GetValue().GetJSON().c_str() << std::endl;
	}
	else
	{
		GameSparksInfo::loginSuccessful = true;
		std::cout << "you successfully authenticated to GameSparks with your credentials" << std::endl;
		std::cout << "your displayname is " << response.GetBaseData().GetString("displayName").GetValue().c_str() << std::endl;
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
		// Login immediately when gamesparks is available
		GameSparksInfo::loginSuccessful = true;
		GameSparks::Api::Requests::AuthenticationRequest request(gsInstance);
		request.SetUserName(GameSparksInfo::username);
		request.SetPassword(GameSparksInfo::password);
		request.Send(AuthenticationRequest_Response);
	}
}

void LeaderboardDataRequest_Response(GS& gsInstance, const LeaderboardDataResponse& response)
{
	if (response.GetHasErrors())
	{
		std::cout << "something went wrong with leaderboard data request" << std::endl;
		std::cout << response.GetErrors().GetValue().GetJSON().c_str() << std::endl;
	}
	else
	{
		gsstl::vector<LeaderboardData> data = response.GetData();

		GameSparksInfo::leaderboardEntry.clear();
		for (gsstl::vector<LeaderboardData>::iterator it = data.begin(); it != data.end(); ++it)
		{
			LeaderboardData data = *it;

			LeaderboardEntry dataEntry;
			dataEntry.username = data.GetBaseData().GetString("userName").GetValue();
			dataEntry.rank = data.GetBaseData().GetLong("rank").GetValue();
			dataEntry.time = data.GetBaseData().GetLong("TIME").GetValue();

			GameSparksInfo::leaderboardEntry.push_back(dataEntry);
		}
	}
}

void AroundMeLeaderboardRequest_Response(GS& gsInstance, const AroundMeLeaderboardResponse& response)
{
	if (response.GetHasErrors())
	{
		std::cout << "something went wrong with around me leaderboard request" << std::endl;
		std::cout << response.GetErrors().GetValue().GetJSON().c_str() << std::endl;
	}
	else
	{
		gsstl::vector<LeaderboardData> data = response.GetData();

		for (gsstl::vector<LeaderboardData>::iterator it = data.begin(); it != data.end(); ++it)
		{
			LeaderboardData data = *it;

			if (GameSparksInfo::username == data.GetBaseData().GetString("userName").GetValue())
			{
				GameSparksInfo::currentPlayer.rank = data.GetBaseData().GetLong("rank").GetValue();
				GameSparksInfo::currentPlayer.time = data.GetBaseData().GetLong("TIME").GetValue();
			}
		}
	}
}

void GameSparksAvailable(GameSparks::Core::GS& gsInstance, bool available)
{
	std::cout << "\nGameSparks is " << (available ? "available" : "not available") << std::endl;

	if (available)
	{
		GameSparksInfo::available = true;

		// Sign In request
		if (GameSparksInfo::signInAccount)
		{
			AuthenticationRequest requestRight(gsInstance);
			requestRight.SetUserName(GameSparksInfo::username);
			requestRight.SetPassword(GameSparksInfo::password);
			requestRight.Send(AuthenticationRequest_Response);
			GameSparksInfo::signInAccount = false;

			AroundMeLeaderboardRequest requestAroundMe(gsInstance);
			requestAroundMe.SetEntryCount(1);
			requestAroundMe.SetLeaderboardShortCode("Race_Times");
			requestAroundMe.Send(AroundMeLeaderboardRequest_Response);
		}

		// Account creation request
		if (GameSparksInfo::registerAccount)
		{
			RegistrationRequest req(gsInstance);
			req.SetUserName(GameSparksInfo::username);
			req.SetPassword(GameSparksInfo::password);
			req.SetDisplayName(GameSparksInfo::username);
			req.Send(RegistrationRequest_Response);
			GameSparksInfo::registerAccount = false;
		}

		LeaderboardDataRequest leaderboard(gsInstance);
		leaderboard.SetEntryCount(10);
		leaderboard.SetLeaderboardShortCode("Race_Times");
		leaderboard.Send(LeaderboardDataRequest_Response);
	}
	else
		GameSparksInfo::available = false;
}
