#ifndef _GAMESPARKSRT_UDPCONNECTMESSAGE_HPP_
#define _GAMESPARKSRT_UDPCONNECTMESSAGE_HPP_

#include <memory>
#include "./AbstractResult.hpp"

namespace System { namespace IO { class Stream; } }

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

	class UDPConnectMessage : public ::GameSparks::RT::AbstractResult
	{
		public:
			static System::Failable<UDPConnectMessage*> Deserialize(System::IO::Stream& stream);

			virtual void Execute() override;

			virtual bool ExecuteAsync() override;

	private:
	};

}}}} /* namespace Com.Gamesparks.Realtime.Proto */

#endif /* _GAMESPARKSRT_UDPCONNECTMESSAGE_HPP_ */
