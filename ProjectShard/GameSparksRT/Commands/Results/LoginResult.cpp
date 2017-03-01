#include "../../Proto/ProtocolParser.hpp"
#include "../../Proto/ProtocolBufferException.hpp"
#include "../../IRTSessionInternal.hpp"
#include "../../Proto/Packet.hpp"
#include <GameSparksRT/GameSparksRT.hpp>
#include "../../../System/String.hpp"

#include "./LoginResult.hpp"

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

System::Failable<LoginResult*> LoginResult::Deserialize(System::IO::Stream& stream)
{
    std::unique_ptr<LoginResult> instance(new LoginResult());
	for (;;)
    {
        GS_ASSIGN_OR_THROW(keyByte, stream.ReadByte());
        if (keyByte == -1)
            break;
        // Optimized reading of known fields with field ID < 16
        switch (keyByte)
        {
            // Field 1 Varint
            case 8:
            {
                GS_ASSIGN_OR_THROW(tmp, GameSparks::RT::Proto::ProtocolParser::ReadBool(stream));
                instance->Success = tmp;
                continue;
            }
            // Field 2 LengthDelimited
            case 18:
            {
                GS_ASSIGN_OR_THROW(tmp, GameSparks::RT::Proto::ProtocolParser::ReadString(stream));
                instance->ReconnectToken = tmp;
                continue;
            }
            // Field 3 Varint
            case 24:
            {
                GS_ASSIGN_OR_THROW(tmp, GameSparks::RT::Proto::ProtocolParser::ReadUInt64(stream));
                instance->PeerId = (int)tmp;
                continue;
            }
            // Field 4 Varint
            case 32:
            {
                // repeated
                GS_ASSIGN_OR_THROW(tmp, GameSparks::RT::Proto::ProtocolParser::ReadUInt64(stream));
                instance->ActivePeers.push_back((int)tmp);
                continue;
            }
            // Field 5 Varint
            case 40:
            {
                GS_ASSIGN_OR_THROW(tmp, ::GameSparks::RT::Proto::ProtocolParser::ReadUInt64(stream));
                instance->FastPort = (int)tmp;
                continue;
            }
        }

        GS_ASSIGN_OR_THROW(key, GameSparks::RT::Proto::ProtocolParser::ReadKey((unsigned char)keyByte, stream))

        // Reading field ID > 16 and unknown field ID/wire type combinations
        switch (key.Field)
        {
            case 0:
                GS_THROW(GameSparks::RT::Proto::ProtocolBufferException("Invalid field id: 0, something went wrong in the stream"));
            default:
                GS_CALL_OR_THROW(GameSparks::RT::Proto::ProtocolParser::SkipKey(stream, key));
                break;
        }
    }

    return instance.release();
}

using GameSparks::RT::GameSparksRT;

void LoginResult::Execute() {
    session->ConnectToken(this->ReconnectToken);
    session->PeerId = this->PeerId;
    if (packet->Reliable.GetValueOrDefault (true)) {
        if (this->FastPort.HasValue() && this->FastPort.Value() != 0) {
            session->FastPort(System::String::ToString(this->FastPort.Value()));
        }

        session->ActivePeers = ActivePeers;
        session->SetConnectState(GameSparksRT::ConnectState::ReliableOnly);
        session->ConnectFast ();
        session->Log ("LoginResult", GameSparksRT::LogLevel::LL_DEBUG, "{0} TCP LoginResult.ActivePeers {1} FastPort {2}", session->PeerId, session->ActivePeers.size(), session->FastPort());
    } else {
        session->SetConnectState(GameSparksRT::ConnectState::ReliableAndFastSend);
        session->Log ("LoginResult", GameSparksRT::LogLevel::LL_DEBUG, "{0} UDP LoginResult, ActivePeers {1}", session->PeerId, session->ActivePeers.size());
    }
}

bool LoginResult::ExecuteAsync() {
    return false;
}

}}}} /* namespace Com.Gamesparks.Realtime.Proto */
