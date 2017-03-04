#ifndef _GAMESPARKSRT_PINGRESULT_HPP_
#define _GAMESPARKSRT_PINGRESULT_HPP_

#include <memory>
#include "./AbstractResult.hpp"

namespace System { namespace IO { class Stream; } }

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

	class PingResult : public ::GameSparks::RT::AbstractResult
	{
		public:
			static System::Failable<PingResult*> Deserialize(System::IO::Stream& stream);
			virtual void Execute() override;
			virtual bool ExecuteAsync() override;
	private:
	};

}}}} /* namespace Com.Gamesparks.Realtime.Proto */

#endif /* _GAMESPARKSRT_PINGRESULT_HPP_ */
