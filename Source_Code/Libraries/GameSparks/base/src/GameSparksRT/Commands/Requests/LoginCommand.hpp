#ifndef _GAMESPARKSRT_LOGINCOMMAND_HPP_
#define _GAMESPARKSRT_LOGINCOMMAND_HPP_

#include "./RTRequest.hpp"
#include <string>
#include "../../Proto/ProtocolParser.hpp"

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

	class LoginCommand : public ::GameSparks::RT::Commands::RTRequest
	{
		public:
			LoginCommand(const std::string connectToken);
			virtual System::Failable<void> Serialize (System::IO::Stream& stream) const override;
			const std::string Token;
			const int ClientVersion;
		private:
			static System::Failable<void> Serialize(System::IO::Stream& stream, const LoginCommand& instance);
			enum { _clientVersion = 2 };
	};

}}}} /* namespace Com.Gamesparks.Realtime.Proto */

#endif /* _GAMESPARKSRT_LOGINCOMMAND_HPP_ */
