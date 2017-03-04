#ifndef GAME_SPARKS_INFO_H
#define GAME_SPARKS_INFO_H

#include "GameSparks\GS.h"
#include "GameSparks\IGSPlatform.h"
#include "GameSparks\generated\GSRequests.h"
#include "GameSparks\generated\GSResponses.h"
#include "GameSparksConfiguration.h"
#include "GameSparks\GSOptional.h"
#include <fstream>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

#include <iostream>
#include <iomanip>
#include "urlmon.h"
#include <wininet.h>

#ifdef _UNICODE
#define tcout wcout
#else
#define tcout cout
#endif

using namespace std;

using namespace GameSparks::Core;
using namespace GameSparks::Api::Responses;
using namespace GameSparks::Api::Requests;
using namespace GameSparks::Api::Types;

struct LeaderboardEntry
{
	GameSparks::Optional::t_StringOptional username;
	GameSparks::Optional::t_LongOptional rank;
	GameSparks::Optional::t_FloatOptional time;
};

struct CurrentPlayer
{
	GameSparks::Optional::t_LongOptional rank;
	GameSparks::Optional::t_FloatOptional time;
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
	static bool logRaceTimeEvent;
	static float worldRaceRecord;
	static GameSparks::Optional::t_StringOptional raceSeedUrl;
	static int logEventFinishTime;
	static int raceTrackSeed;

	static void Update();
	static bool GetStatus();
	static void InitGS();

private:
	static GS gs;
	static GameSparksConfiguration::NativePlatformDescription platform;
	static gsstl::string message;
};

#endif