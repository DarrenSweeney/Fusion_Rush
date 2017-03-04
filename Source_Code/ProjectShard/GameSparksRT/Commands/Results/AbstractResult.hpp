#ifndef _GAMESPARKSRT_ABSTRACTRESULT_HPP_
#define _GAMESPARKSRT_ABSTRACTRESULT_HPP_

#include <GameSparksRT/Forwards.hpp>
#include "../../IRTCommand.hpp"

namespace GameSparks { namespace RT {

	class AbstractResult : public IRTCommand
	{
		public:
			void Configure(const Proto::Packet& packet_, IRTSessionInternal& session_)
			{
				this->packet = &packet_;
				this->session = &session_;
			}

			virtual bool ExecuteAsync()
			{
				return true;
			}

			virtual AbstractResult* asAbstractResult() { return this; }
		protected:
			const Proto::Packet* packet = nullptr;
			IRTSessionInternal* session = nullptr;

	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_ABSTRACTRESULT_HPP_ */
