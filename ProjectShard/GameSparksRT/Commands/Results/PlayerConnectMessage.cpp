#include "../../Proto/ProtocolParser.hpp"
#include "../../Proto/ProtocolBufferException.hpp"
#include "../../IRTSessionInternal.hpp"
#include "./PlayerConnectMessage.hpp"

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

System::Failable<PlayerConnectMessage*> PlayerConnectMessage::Deserialize(System::IO::Stream& stream)
{
    std::unique_ptr<PlayerConnectMessage> instance(new PlayerConnectMessage());

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
                GS_ASSIGN_OR_THROW(tmp, ::GameSparks::RT::Proto::ProtocolParser::ReadUInt64(stream));
                instance->PeerId = (int)tmp;
                continue;
            }
            // Field 4 Varint
            case 32:
            {
                // repeated
                GS_ASSIGN_OR_THROW(tmp, ::GameSparks::RT::Proto::ProtocolParser::ReadUInt64(stream));
                instance->ActivePeers.push_back((int)tmp);
                continue;
            }
        }

        GS_ASSIGN_OR_THROW(key, ::GameSparks::RT::Proto::ProtocolParser::ReadKey((unsigned char)keyByte, stream));

        // Reading field ID > 16 and unknown field ID/wire type combinations
        switch (key.Field)
        {
            case 0:
                GS_THROW(::GameSparks::RT::Proto::ProtocolBufferException("Invalid field id: 0, something went wrong in the stream"));
            default:
                GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::SkipKey(stream, key));
                break;
        }
    }

    return instance.release();
}


void PlayerConnectMessage::Execute() {
    session->ActivePeers = this->ActivePeers;
    session->Log ("PlayerConnectMessage", GameSparks::RT::GameSparksRT::LogLevel::LL_DEBUG, "PeerId={0}, ActivePeers {1}", PeerId, session->ActivePeers.size());
    session->OnPlayerConnect (PeerId);
}


}}}} /* namespace Com.Gamesparks.Realtime.Proto */
