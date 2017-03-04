#include <GameSparksRT/Proto/RTVal.hpp>
#include <iostream>
#include "./CustomCommand.hpp"
#include "../IRTSessionInternal.hpp"

namespace GameSparks { namespace RT {


System::Failable<CustomCommand*> CustomCommand::Deserialize(int opCode, int sender, System::IO::Stream& lps, const RTData& data, int limit, const IRTSessionInternal& session)
{
    std::unique_ptr<CustomCommand> instance(new CustomCommand(opCode, sender, data, limit, session));
    GS_CALL_OR_THROW(lps.Read(instance->payload, 0, limit));
    return instance.release();
}


CustomCommand::CustomCommand(int opCode_, int sender_, const RTData& data_, int limit_, const IRTSessionInternal& session_)
:session(session_)
,opCode(opCode_)
,sender(sender_)
,data(data_)
,payload(limit_)
{
}


void CustomCommand::Execute()
{
    if(session.SessionListener)
    {
        session.SessionListener->OnPacket(RTPacket(opCode, sender, payload, data));
    }
    else
    {
        std::clog << "INFO: no session SessionListener registered on session." << std::endl;
    }
}

}} /* namespace GameSparks.RT */
