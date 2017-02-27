#include <iostream>

#include <GameSparks/GS.h>
#include <GameSparks/generated/GSRequests.h>
#include <GameSparks/generated/GSMessages.h>
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
	gs.SetMessageListener<GameSparks::Api::Messages::ScriptMessage>([&platform](GS&, const GameSparks::Api::Messages::ScriptMessage& message){
		if (!message.GetHasErrors())
		{
			platform.DebugMsg("Received Message from server. Durable request was sent successfully");
		}
	});
	gs.GameSparksAvailable = [&platform](GS& gs2, bool available){
		if (!available)
		{
			platform.DebugMsg("not available");
			return;
		}
		GameSparks::Api::Requests::DeviceAuthenticationRequest authRequest(gs2);
		authRequest.SetDeviceId(platform.GetDeviceId());
		authRequest.SetDeviceOS(platform.GetDeviceOS());

		authRequest.Send([&platform](GS& instance, const GameSparks::Api::Responses::AuthenticationResponse& response){

			if (!response.GetHasErrors())
			{

				//
				// You can add some cloud code to send a message to the client once the "testMessage" is received on the server side.
				// It should look something like this:
				//
				//		var player = Spark.getPlayer();
				//		var requestData = Spark.getData();
				//
				//		Spark.sendMessage(requestData, player);
				//
				// This will trigger the global message callback. The program will log whenever it receives such a message: 
				// "Received Message from server. Durable request was sent successfully"

				GameSparks::Api::Requests::LogEventRequest logEvent(instance);
				logEvent.SetEventKey("testMessage");
				logEvent.SetEventAttribute("foo", "bar");
				logEvent.SetDurable(true);

				//
				// # 1 Store durable requests
				// To test the durable-flag you can use the following code.
				// The request will be written to disk and then the program will exit immediately. 
				// The request should reside in local storage at this point. 
				//
				//
				// # 2 Resend durable requests from local storage
				// If you start the program with the following lines commented out
				// it will read the durable request from disk and will try to send it. 
				//

				//logEvent.Send();
				//exit(0);

				//
				// # Send a durable request directly
				// If there is a network connection in place the durable request will be written to disk, sent and then removed from disk. 
				//
				
				//logEvent.Send();
			}
			else
			{
				platform.DebugMsg( response.GetErrors().GetValue().GetJSON() );
			}
		});
	};


	int cyclesLeft = 200;
	while (cyclesLeft-- > 0)
	{
		// deltaTime has to be provided in seconds
		gs.Update(0.1f);
		usleep(100000);
	}
	std::string foo;
	std::cin >> foo;

	gs.ShutDown();
}
