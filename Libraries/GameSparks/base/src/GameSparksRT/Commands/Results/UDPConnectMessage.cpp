#include "../../Proto/ProtocolParser.hpp"
#include "../../Proto/ProtocolBufferException.hpp"
#include "../../Proto/Packet.hpp"
#include "../../IRTSessionInternal.hpp"
#include "./UDPConnectMessage.hpp"

using namespace GameSparks::RT;

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

System::Failable<UDPConnectMessage*> UDPConnectMessage::Deserialize(System::IO::Stream& stream)
{
    std::unique_ptr<UDPConnectMessage> instance(new UDPConnectMessage());

	for (;;)
    {
        GS_ASSIGN_OR_THROW(keyByte, stream.ReadByte());
        if (keyByte == -1)
            break;

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

void UDPConnectMessage::Execute() {
    session->Log("UDPConnectMessage", GameSparksRT::LogLevel::LL_DEBUG, "(UDP) reliable={0}, ActivePeers {1}", packet->Reliable.GetValueOrDefault(false), session->ActivePeers.size());
    if (!packet->Reliable.GetValueOrDefault (false)) {
        session->SetConnectState(GameSparksRT::ConnectState::ReliableAndFast);
        //TODO: check if passing empty objects is valid, or if they have to be nullable
        session->SendData (-5, GameSparksRT::DeliveryIntent::RELIABLE, /*nullptr*/{}, /*nullptr*/{}, {});
    } else {
        session->Log ("UDPConnectMessage", GameSparksRT::LogLevel::LL_DEBUG, "TCP (Unexpected) UDPConnectMessage");
    }
}

bool UDPConnectMessage::ExecuteAsync() {
    return false;
}

}}}} /* namespace Com.Gamesparks.Realtime.Proto */
