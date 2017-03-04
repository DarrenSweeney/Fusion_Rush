#include "../IRTCommand.hpp"
#include "./Packet.hpp"
#include "RTData.Serializer.hpp"
#include "../Commands/CommandFactory.hpp"
#include "../../System/Failable.hpp"

namespace GameSparks { namespace RT { namespace Proto {

System::Failable<System::Bytes> Packet::ReadPayload (System::IO::Stream& stream)
{
    hasPayload = true;
	assert(Session);

    GS_ASSIGN_OR_THROW(tmp, Commands::CommandFactory::GetCommand (OpCode, Sender.GetValueOrDefault(0), SequenceNumber, stream, *Session, Data));
    Command = decltype(Command)(tmp);
    return System::Failable<System::Bytes>(System::Bytes()); // TODO: why does this return null in C# ?
}


RTVal::RTVal() {}
RTVal::RTVal(int64_t value) : long_val(value) {}
RTVal::RTVal(float value) : float_val(value) {}
RTVal::RTVal(double value) : double_val(value) {}
RTVal::RTVal(const std::string &value) : string_val(value) {}
RTVal::RTVal(const RTData &value) : data_val(value) {}
RTVal::RTVal(const RTVector &value) : vec_val(value) {}


std::ostream &operator<<(std::ostream &os, const RTVal &val) {
         if(val.long_val.HasValue()) os << val.long_val.Value();
    else if(val.float_val.HasValue()) os << val.float_val.Value();
    else if(val.double_val.HasValue()) os << val.double_val.Value();
    else if(val.data_val.HasValue()) os << val.data_val.Value();
    else if(val.string_val.HasValue()) os << val.string_val.Value();
    else if(val.vec_val.HasValue()) os << val.vec_val.Value();

    return os;
}


System::Failable<void> RTVal::DeserializeLengthDelimited(System::IO::Stream &stream, System::IO::BinaryReader &br, RTVal& instance) {
    /// TODO: Exception handling: check return type.
    GS_CALL_OR_THROW(RTValSerializer::ReadRTVal (stream, br, instance));
    return {};
}


System::Failable<void> RTVal::SerializeLengthDelimited(System::IO::Stream &stream) {
    assert(this);
    GS_CALL_OR_THROW(RTValSerializer::WriteRTVal (stream, *this));
    return {};
}


RTVal::operator bool() const {
    return long_val.HasValue() ||
        float_val.HasValue() ||
        double_val.HasValue() ||
        data_val.HasValue() ||
        string_val.HasValue() ||
        vec_val.HasValue();
}

}}} /* namespace GameSparks.RT.Proto */
