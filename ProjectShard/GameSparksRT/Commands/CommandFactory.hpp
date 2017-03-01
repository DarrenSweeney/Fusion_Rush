#ifndef _GAMESPARKSRT_COMMANDFACTORY_HPP_
#define _GAMESPARKSRT_COMMANDFACTORY_HPP_

#include <memory>

#include <System/Nullable.hpp>
#include <GameSparksRT/Forwards.hpp>

namespace GameSparks { namespace RT { namespace Commands {

	class CommandFactory
	{
		public:
			static System::Failable<IRTCommand*> GetCommand(int opCode, int sender, System::Nullable<int> sequence,
														  System::IO::Stream &stream, IRTSessionInternal &session,
														  RTData &data);

		private:
	};

	class OpCodes
	{
		public:
			enum Unnamed
			{
				LoginResult = -1,
				PingResult = -3,
				UDPConnectMessage = -5,
				PlayerReadyMessage = -7,
				PlayerConnectMessage = -101,
				PlayerDisconnectMessage = -103
			};

			//public const int LoginResult = -1;
			//public const int PingResult = -3;
			//public const int UDPConnectMessage = -5;
			//public const int PlayerReadyMessage = -7;
			//public const int PlayerConnectMessage = -101;
			//public const int PlayerDisconnectMessage = -103;

		private:
	};

}}} /* namespace GameSparks.RT.Commands */

#endif /* _GAMESPARKSRT_COMMANDFACTORY_HPP_ */
