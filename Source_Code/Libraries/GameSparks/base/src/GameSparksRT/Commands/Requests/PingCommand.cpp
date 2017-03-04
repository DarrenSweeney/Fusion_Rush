#include "./PingCommand.hpp"
#include "../../../System/IO/MemoryStream.hpp"
#include "../../Proto/ProtocolParser.hpp"

namespace Com { namespace Gamesparks { namespace Realtime { namespace Proto {

PingCommand::PingCommand() : RTRequest(-2) {}

System::Failable<void> PingCommand::Serialize(System::IO::Stream &stream) const {
    GS_CALL_OR_THROW(PingCommand::Serialize(stream, *this));
    return {};
}

System::Failable<void> PingCommand::Serialize(System::IO::Stream &/*stream*/, const PingCommand &/*instance*/) {
    assert(false); // not yet implemented (in C# SDK)
    GS_PROGRAMMING_ERROR("should never be called");
    return {};
}

System::Failable<void> PingCommand::SerializeLengthDelimited(System::IO::Stream &stream, PingCommand instance) {
    System::IO::MemoryStream ms;

    GS_CALL_OR_THROW(Serialize(ms, instance));
    auto data = ms.GetBuffer();
    GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteUInt32(stream, (unsigned int)ms.Position()));
    GS_CALL_OR_THROW(stream.Write(data, 0, (int)ms.Position()));
    return {};
}

}}}} /* namespace Com.Gamesparks.Realtime.Proto */
