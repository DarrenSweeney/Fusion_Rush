#ifndef _GAMESPARKSRT_ACTIONCOMMAND_HPP_
#define _GAMESPARKSRT_ACTIONCOMMAND_HPP_

#include "../IRTCommand.hpp"
#include "../../System/Action.hpp"
#include <cassert>

namespace GameSparks { namespace RT {

	class ActionCommand : public IRTCommand
	{
		public:
			ActionCommand(const System::Action& action_) : action(action_) {assert(action);}
			virtual void Execute() override;
		private:
			System::Action action;
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_ACTIONCOMMAND_HPP_ */
