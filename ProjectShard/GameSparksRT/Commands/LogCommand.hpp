#ifndef _GAMESPARKSRT_LOGCOMMAND_HPP_
#define _GAMESPARKSRT_LOGCOMMAND_HPP_

#include "../IRTCommand.hpp"
#include <string>
#include <GameSparksRT/GameSparksRT.hpp>

namespace GameSparks { namespace RT {

	class LogCommand : public IRTCommand
	{
		public:
			LogCommand(const std::string& tag, GameSparks::RT::GameSparksRT::LogLevel level, const std::string& msg);
			virtual void Execute() override;
		private:
			const std::string tag, msg;
			const GameSparks::RT::GameSparksRT::LogLevel level;
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_LOGCOMMAND_HPP_ */
