#ifndef _GAMESPARKSRT_PINGCOMMAND_HPP_
#define _GAMESPARKSRT_PINGCOMMAND_HPP_

#include "./RTRequest.hpp"

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

	class PingCommand : public ::GameSparks::RT::Commands::RTRequest
	{
		public:
			PingCommand();
		private:
			virtual System::Failable<void> Serialize (System::IO::Stream& stream) const override;
			static  System::Failable<void> Serialize(System::IO::Stream& stream, const PingCommand& instance);
			static  System::Failable<void> SerializeLengthDelimited(System::IO::Stream& stream, PingCommand instance);
	};

}}}} /* namespace Com.Gamesparks.Realtime.Proto */

#endif /* _GAMESPARKSRT_PINGCOMMAND_HPP_ */
