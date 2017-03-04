#pragma once

#include <iostream>

#include <GameSparks/GS.h>
#include <GameSparks/IGSPlatform.h>
#include <GameSparks/gsstl.h>

namespace SampleConfiguration
{
	using namespace GameSparks;
	using namespace GameSparks::Core;
	using namespace GameSparks::Optional;

	class NativePlatformDescription : public IGSPlatform
	{
	public:
		NativePlatformDescription()
		:IGSPlatform
		(
			"<GameSparks Api Key>", // insert your auth key
			"<GameSparks Api Secret>", // insert your secret
			true, // use the preview server?
			true // do you want verbose debugging?
		)
		{
			SetRequestTimeoutSeconds(5);
		}

		/*virtual gsstl::string GetDeviceId() const
		{
			return "unique_device";
		}*/

		virtual gsstl::string GetSDK() const
		{
			return "GameSparks SDK C++ 1.0";
		}

		virtual gsstl::string GetDeviceType() const
		{
			return "Desktop";
		}

		virtual void DebugMsg(const gsstl::string& message) const
		{
			std::cout << "[" << GSDateTime::Now().ToString().c_str() << "] GameSparks API: " << message.c_str() << std::endl;
		}
	};
}
