#include <GameSparksRT/GameSparksRT.hpp>
#include "../../Proto/ProtocolParser.hpp"
#include "../../Proto/ProtocolBufferException.hpp"
#include "../../IRTSessionInternal.hpp"
#include "./PingResult.hpp"

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

System::Failable<PingResult*> PingResult::Deserialize(System::IO::Stream& stream)
{
    std::unique_ptr<PingResult> instance(new PingResult());

	for (;;)
    {
        GS_ASSIGN_OR_THROW(keyByte, stream.ReadByte());
        if (keyByte == -1)
            break;
        GS_ASSIGN_OR_THROW(key, GameSparks::RT::Proto::ProtocolParser::ReadKey((unsigned char)keyByte, stream));

        // Reading field ID > 16 and unknown field ID/wire type combinations
        switch (key.Field)
        {
            case 0:
                return GameSparks::RT::Proto::ProtocolBufferException("Invalid field id: 0, something went wrong in the stream");
            default:
                GS_CALL_OR_THROW(GameSparks::RT::Proto::ProtocolParser::SkipKey(stream, key));
                break;
        }
    }

    return instance.release();
}

void PingResult::Execute() {
    assert(session);
    session->Log ("PingResult", GameSparks::RT::GameSparksRT::LogLevel::LL_DEBUG, "");
}

bool PingResult::ExecuteAsync() {
    return false;
}

}}}} /* namespace Com.Gamesparks.Realtime.Proto */

	