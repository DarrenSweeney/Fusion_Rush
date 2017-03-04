#include "../Proto/ProtocolParser.hpp"
#include "./CommandFactory.hpp"

#include "../Commands/Results/LoginResult.hpp"
#include "../Commands/Results/PingResult.hpp"
#include "../Commands/Results/UDPConnectMessage.hpp"
#include "../Commands/Results/PlayerConnectMessage.hpp"
#include "../Commands/Results/PlayerDisconnectMessage.hpp"
#include "../Commands/CustomCommand.hpp"
#include "../IRTSessionInternal.hpp"
#include <iostream>

using namespace GameSparks::RT::Proto;
using namespace Com::Gamesparks::Realtime::Proto;

namespace GameSparks { namespace RT { namespace Commands {

System::Failable<IRTCommand*> CommandFactory::GetCommand(int opCode, int sender, System::Nullable<int> sequence,
                                                       System::IO::Stream &stream, IRTSessionInternal &session,
                                                       RTData &data)
{
    GS_ASSIGN_OR_THROW(limit, GameSparks::RT::Proto::ProtocolParser::ReadUInt32(stream));

    LimitedPositionStream lps(stream, limit);
    GS_TRY
    {
        switch (opCode) {
            case OpCodes::LoginResult:
                GS_RETURN_OR_CATCH(LoginResult::Deserialize(lps));
            case OpCodes::PingResult:
                GS_RETURN_OR_CATCH(PingResult::Deserialize(lps));
            case OpCodes::UDPConnectMessage:
                GS_RETURN_OR_CATCH(UDPConnectMessage::Deserialize(lps));
            case OpCodes::PlayerConnectMessage:
                GS_RETURN_OR_CATCH(PlayerConnectMessage::Deserialize(lps));
            case OpCodes::PlayerDisconnectMessage:
                GS_RETURN_OR_CATCH(PlayerDisconnectMessage::Deserialize(lps));
            default:
            {
                if(session.ShouldExecute(sender, sequence)){
                    GS_RETURN_OR_CATCH(CustomCommand::Deserialize(opCode, sender, lps, data, (int)limit, session));
                }
                return nullptr;
            }
        }
    }
    GS_CATCH(e)
    {
        std::clog << "exception: " << e.Format() << std::endl;
        GS_THROW(e);
        //assert(false);
		//return nullptr;
    }
    return nullptr;
}


}}} /* namespace GameSparks.RT.Commands */

	