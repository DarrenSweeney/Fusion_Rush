#include <iostream>

#include <GameSparks/GS.h>
#include <GameSparks/IGSPlatform.h>

#include "./extra/usleep.h"
#include "sample_configuration.h"

int main(int argc, const char* argv[])
{
    (void)(argc); // unused
    (void)(argv); // unused

    using namespace GameSparks::Core;

	GS gs;
    SampleConfiguration::NativePlatformDescription platform;
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
