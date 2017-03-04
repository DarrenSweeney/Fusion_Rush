#ifndef _GAMESPARKSRT_PLAYERCONNECTMESSAGE_HPP_
#define _GAMESPARKSRT_PLAYERCONNECTMESSAGE_HPP_

#include "./AbstractResult.hpp"
#include <memory>
#include <vector>

namespace System { namespace IO { class Stream; } }

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

	class PlayerConnectMessage : public ::GameSparks::RT::AbstractResult
	{
		public:
			int PeerId = -1;
			std::vector<int> ActivePeers;

			static System::Failable<PlayerConnectMessage*> Deserialize(System::IO::Stream& stream);
			virtual void Execute() override;
		private:
	};

}}}} /* namespace Com.Gamesparks.Realtime.Proto */

#endif /* _GAMESPARKSRT_PLAYERCONNECTMESSAGE_HPP_ */
