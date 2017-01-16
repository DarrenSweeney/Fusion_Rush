#ifndef GAME_SPARKS_INFO_H
#define GAME_SPARKS_INFO_H

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

struct LeaderboardEntry
{
	GameSparks::Optional::t_StringOptional username;
	GameSparks::Optional::t_LongOptional rank;
	// TODO(Darren): May have to store this in milisecond and convert
	GameSparks::Optional::t_LongOptional time;
};

struct CurrentPlayer
{
	GameSparks::Optional::t_LongOptional rank;
	// TODO(Darren): May have to store this in milisecond and convert
	GameSparks::Optional::t_LongOptional time;
};

class GameSparksInfo
{
public:
	GameSparksInfo();
	~GameSparksInfo();

	static bool available;
	static std::vector<LeaderboardEntry> leaderboardEntry;
	static CurrentPlayer currentPlayer;
	static std::string username, password;
	static bool registerAccount, signInAccount;
	static bool loginSuccessful;
	static std::string currentPlayerRank;

	void Update();
	bool GetStatus();
	void InitGS();

private:
	GS gs;
	GameSparksConfiguration::NativePlatformDescription platform;
	gsstl::string message;
};

#endif