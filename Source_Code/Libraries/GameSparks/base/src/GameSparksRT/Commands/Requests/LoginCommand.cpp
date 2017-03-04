#include "./LoginCommand.hpp"

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {


LoginCommand::LoginCommand(const std::string connectToken)
: RTRequest(0)
, Token(connectToken)
, ClientVersion(_clientVersion){ }


System::Failable<void> LoginCommand::Serialize (System::IO::Stream& stream) const{
    GS_CALL_OR_THROW(LoginCommand::Serialize(stream, *this));
    return {};
}


System::Failable<void> LoginCommand::Serialize(System::IO::Stream& stream, const LoginCommand& instance)
{
    if (!instance.Token.empty())
    {
        // Key for field: 1, LengthDelimited
        GS_CALL_OR_THROW(stream.WriteByte(10));
        GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteBytes(stream, System::Text::Encoding::UTF8::GetBytes(instance.Token)));
    }

    //if (instance.ClientVersion != null)
    {
        // Key for field: 2, Varint
        GS_CALL_OR_THROW(stream.WriteByte(16));
        GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteUInt64(stream,(uint64_t)instance.ClientVersion));
    }
    return {};
}

}}}} /* namespace Com.Gamesparks.Realtime.Proto */

	