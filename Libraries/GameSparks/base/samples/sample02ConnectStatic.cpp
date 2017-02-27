#include <iostream>

#include <GameSparks/GS.h>
#include <GameSparks/IGSPlatform.h>

#include "./extra/usleep.h"
#include "sample_configuration.h"

// we no longer provide a global GS-instance, but of cause you create your own:
GameSparks::Core::GS gs;

// but note, that the platform instance has to exist as long as GS in running:
SampleConfiguration::NativePlatformDescription platform;

void CreateSmallGameSparksSession()
{
	using namespace GameSparks::Core;

	gs.Initialise(&platform);

	int cyclesLeft = 200;
	while (cyclesLeft-- > 0)
	{
		// deltaTime has to be provided in seconds
		gs.Update(0.1f);
		usleep(100000);
	}

	gs.ShutDown();
}


int main(int argc, const char* argv[])
{
    (void)(argc); // unused
    (void)(argv); // unused

    CreateSmallGameSparksSession();
	// double check if GS can run twice in a row without problems
	CreateSmallGameSparksSession();

	return 0;
}
