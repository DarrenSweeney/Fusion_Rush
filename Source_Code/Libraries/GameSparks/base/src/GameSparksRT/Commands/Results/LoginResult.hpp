#ifndef _GAMESPARKSRT_LOGINRESULT_HPP_
#define _GAMESPARKSRT_LOGINRESULT_HPP_

#include "./AbstractResult.hpp"
#include "../../IRTCommand.hpp"
#include <System/Nullable.hpp>
#include <string>
#include <vector>

namespace System { namespace IO { class Stream; } }

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

	class LoginResult : public ::GameSparks::RT::AbstractResult//, public ::GameSparks::RT::IRTCommand
	{
		public:
			bool Success;
			std::string ReconnectToken;
			System::Nullable<int> PeerId;
			std::vector<int> ActivePeers;
			System::Nullable<int> FastPort;

			static System::Failable<LoginResult*> Deserialize(System::IO::Stream& stream);
			virtual void Execute() override;

			virtual bool ExecuteAsync() override;
		private:
	};

}}}} /* namespace Com.Gamesparks.Realtime.Proto */

#endif /* _GAMESPARKSRT_LOGINRESULT_HPP_ */
