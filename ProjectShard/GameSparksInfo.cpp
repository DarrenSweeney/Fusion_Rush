#include "GameSparksInfo.h"

void AuthenticationRequest_Response(GameSparks::Core::GS&, const GameSparks::Api::Responses::AuthenticationResponse& response);
void RegistrationRequest_Response(GS& gsInstance, const GameSparks::Api::Responses::RegistrationResponse& response);
void LeaderboardDataRequest_Response(GS& gsInstance, const LeaderboardDataResponse& response);
void GameSparksAvailable(GameSparks::Core::GS& gsInstance, bool available);
void GetLeaderboardEntriesRequest_Response(GS& gsInstance, const GetLeaderboardEntriesResponse& response);

std::vector<LeaderboardEntry> GameSparksInfo::leaderboardEntry;
std::string GameSparksInfo::signInUsername, GameSparksInfo::signInPassword;
std::string GameSparksInfo::accountRegUsername, GameSparksInfo::accountRegPassword;
bool GameSparksInfo::loginSuccessful;
bool GameSparksInfo::registerAccount;
bool GameSparksInfo::available;
std::string GameSparksInfo::currentPlayerRank;

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

		// TODO(Darren): Check what errors i get here and feed them back into the menu
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
		GameSparks::Api::Requests::AuthenticationRequest request(gsInstance);
		request.SetUserName(GameSparksInfo::accountRegUsername);
		request.SetPassword(GameSparksInfo::accountRegPassword);
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

void GetLeaderboardEntriesRequest_Response(GS& gsInstance, const GetLeaderboardEntriesResponse& response)
{
	if (response.GetHasErrors())
	{
		std::cout << "something went wrong with leaderboard enteries request responce" << std::endl;
		std::cout << response.GetErrors().GetValue().GetJSON().c_str() << std::endl;
	}
	else
	{
		GameSparks::Core::GSData::t_Optional data = response.GetResults();

		GameSparksInfo::currentPlayerRank = data.GetValue().GetString("rank").GetValue();
	}
}

void GameSparksAvailable(GameSparks::Core::GS& gsInstance, bool available)
{
	std::cout << "\nGameSparks is " << (available ? "available" : "not available") << std::endl;

	if (available)
	{
		GameSparksInfo::available = true;

		// Sign In request
		GameSparks::Api::Requests::AuthenticationRequest requestRight(gsInstance);
		requestRight.SetUserName(GameSparksInfo::signInUsername);
		requestRight.SetPassword(GameSparksInfo::signInPassword);
		requestRight.Send(AuthenticationRequest_Response);

		// Account creation request
		if (GameSparksInfo::registerAccount)
		{
			GameSparks::Api::Requests::RegistrationRequest req(gsInstance);
			req.SetUserName(GameSparksInfo::accountRegUsername);
			req.SetPassword(GameSparksInfo::accountRegPassword);
			req.SetDisplayName(GameSparksInfo::accountRegUsername);
			req.Send(RegistrationRequest_Response);
			GameSparksInfo::registerAccount = false;
		}

		GameSparks::Api::Requests::LeaderboardDataRequest leaderboard(gsInstance);
		leaderboard.SetEntryCount(10);
		leaderboard.SetLeaderboardShortCode("Race_Times");
		leaderboard.Send(LeaderboardDataRequest_Response);

		GetLeaderboardEntriesRequest request(gsInstance);
		std::vector<std::string> leaderboards;
		leaderboards.push_back("Race_Times");
		request.SetLeaderboards(leaderboards);
		request.SetPlayer(GameSparksInfo::signInUsername);
		request.Send(GetLeaderboardEntriesRequest_Response);
	}
	else
		GameSparksInfo::available = false;
}
