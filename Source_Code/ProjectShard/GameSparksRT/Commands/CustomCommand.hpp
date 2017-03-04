#ifndef _GAMESPARKSRT_CUSTOMCOMMAND_HPP_
#define _GAMESPARKSRT_CUSTOMCOMMAND_HPP_

#include <GameSparksRT/Forwards.hpp>
#include "../IRTCommand.hpp"
#include "../Proto/LimitedPositionStream.hpp"
#include "../../System/IO/MemoryStream.hpp"
#include <GameSparksRT/RTData.hpp>

namespace GameSparks { namespace RT {

	class CustomCommand : public IRTCommand
	{
		public:
			static System::Failable<CustomCommand*> Deserialize(int opCode, int sender, System::IO::Stream& lps, const RTData& data, int limit, const IRTSessionInternal& session);
			virtual void Execute() override;
		private:
			CustomCommand(int opCode, int sender, const RTData& data, int limit, const IRTSessionInternal& session);
			const IRTSessionInternal& session;
			int opCode, sender;
			RTData data;
			System::Bytes payload;
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_CUSTOMCOMMAND_HPP_ */
