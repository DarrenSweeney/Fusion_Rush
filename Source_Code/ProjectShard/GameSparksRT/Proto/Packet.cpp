#include "../../System/IO/MemoryStream.hpp"
#include "./Packet.hpp"
#include "ProtocolParser.hpp"
#include "../Commands/Requests/RTRequest.hpp"
#include "ProtocolBufferException.hpp"
#include "../../System/IO/EndOfStreamException.hpp"

namespace GameSparks { namespace RT { namespace Proto {

System::Failable<void> Packet::Serialize(System::IO::Stream& stream, const Packet& instance)
{
    // Key for field: 1, Varint
    GS_CALL_OR_THROW(stream.WriteByte(8));
    GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteZInt32(stream, instance.OpCode));
    if (instance.SequenceNumber.HasValue())
    {
        // Key for field: 2, Varint
        GS_CALL_OR_THROW(stream.WriteByte(16));
        GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteUInt64(stream,(uint64_t) instance.SequenceNumber.Value()));
    }
    if (instance.RequestId.HasValue())
    {
        // Key for field: 3, Varint
        GS_CALL_OR_THROW(stream.WriteByte(24));
        GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteUInt64(stream,(uint64_t) instance.RequestId.Value()));
    }
    if (!instance.TargetPlayers.empty())
    {
        for (const auto& i4 : instance.TargetPlayers)
        {
            // Key for field: 4, Varint
            GS_CALL_OR_THROW(stream.WriteByte(32));
            GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteUInt64(stream,(uint64_t)i4));
        }
    }
    if (instance.Sender.HasValue())
    {
        // Key for field: 5, Varint
        GS_CALL_OR_THROW(stream.WriteByte(40));
        GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteUInt64(stream,(uint64_t) instance.Sender.Value()));
    }
    if (instance.Reliable.HasValue())
    {
        // Key for field: 6, Varint
        GS_CALL_OR_THROW(stream.WriteByte(48));
        GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteBool(stream, instance.Reliable.Value()));
    }
    //if(true/*instance.Data*/)
	{
        GS_CALL_OR_THROW(stream.WriteByte(114));
        GS_CALL_OR_THROW(RTData::WriteRTData(stream, instance.Data));
    }
    GS_CALL_OR_THROW(instance.WritePayload(stream));
    return {};
}


System::Failable<int> Packet::SerializeLengthDelimited(System::IO::Stream &stream, const Packet &instance)
{
    System::IO::MemoryStream ms;// = PooledObjects.MemoryStreamPool.Pop ();

    GS_CALL_OR_THROW(Serialize(ms, instance));
    const auto& data = ms.GetBuffer();
    //int64_t pos = ms.Position();
    GS_CALL_OR_THROW(GameSparks::RT::Proto::ProtocolParser::WriteUInt32(stream, (unsigned int)ms.Position()));
    GS_CALL_OR_THROW(stream.Write(data, 0, (int)ms.Position()));
    return ms.Position();
}

System::Failable<void> Packet::WritePayload(System::IO::Stream &stream) const
{
    if (Request != nullptr) {
        // Key for field: 15, LengthDelimited
        System::IO::MemoryStream ms;// = PooledObjects.MemoryStreamPool.Pop();

            GS_CALL_OR_THROW(Request->Serialize (ms));
            auto written = ms.GetBuffer();
            if (ms.Position() > 0) {
                GS_CALL_OR_THROW(stream.WriteByte (122));
                GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteBytes (stream, written, (int)ms.Position()));
            }
    } else {
        if (!Payload.empty())
        {
            // Key for field: 15, LengthDelimited
            GS_CALL_OR_THROW(stream.WriteByte(122));
            GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteBytes(stream, Payload));
        }
    }
    return {};
}


System::Failable<void> Packet::DeserializeLengthDelimited(System::IO::Stream &stream, System::IO::BinaryReader &br, Packet& instance)
{
    GS_ASSIGN_OR_THROW(limit_, ::GameSparks::RT::Proto::ProtocolParser::ReadUInt32(stream));
    int limit = static_cast<int>(limit_);
    limit += stream.Position();

	for (;;)
    {
        if (stream.Position() >= limit)
        {
            if (stream.Position() == limit)
                break;
            else
                return GameSparks::RT::Proto::ProtocolBufferException("Read past max limit");
        }

        GS_ASSIGN_OR_THROW(keyByte, stream.ReadByte());

        if (keyByte == -1)
            GS_THROW(System::IO::EndOfStreamException("EndOfStreamException"));
        // Optimized reading of known fields with field ID < 16
        switch (keyByte)
        {
            // Field 1 Varint
            case 8:
            {
                GS_ASSIGN_OR_THROW(tmp, ::GameSparks::RT::Proto::ProtocolParser::ReadZInt32 (stream));
                instance.OpCode = tmp;
                continue;
                // Field 2 Varint
            }
            case 16:
            {
                GS_ASSIGN_OR_THROW(tmp, ::GameSparks::RT::Proto::ProtocolParser::ReadUInt64(stream));
                instance.SequenceNumber = (int)tmp;
                continue;
            }
            // Field 3 Varint
            case 24:
            {
                GS_ASSIGN_OR_THROW(tmp, ::GameSparks::RT::Proto::ProtocolParser::ReadUInt64(stream));
                instance.RequestId = (int)tmp;
                continue;
            }
            // Field 5 Varint
            case 40:
            {
                GS_ASSIGN_OR_THROW(tmp, ::GameSparks::RT::Proto::ProtocolParser::ReadUInt64(stream));
                instance.Sender = (int)tmp;
                continue;
            }
            // Field 6 Varint
            case 48:
            {
                GS_ASSIGN_OR_THROW(tmp, ::GameSparks::RT::Proto::ProtocolParser::ReadBool(stream));
                instance.Reliable = tmp;
                continue;
            }
            // Field 7 Varint
            case 114:
            {
                /*if (instance.Data == nullptr)
                    instance.Data = RTData.ReadRTData(stream, br, instance.Data);
                else*/
                GS_CALL_OR_THROW(RTData::ReadRTData(stream, br, instance.Data));
                continue;
            }
            // Field 15 LengthDelimited
            case 122:
            {
                // note: ReadPayload always return null. the payload is stored in a MemoryStream withing a CustomCommand
                GS_ASSIGN_OR_THROW(tmp, instance.ReadPayload(stream));
                instance.Payload = tmp;
                continue;
            }
        }

        GS_ASSIGN_OR_THROW(key, ::GameSparks::RT::Proto::ProtocolParser::ReadKey((unsigned char)keyByte, stream));

        // Reading field ID > 16 and unknown field ID/wire type combinations
        switch (key.Field)
        {
            case 0:
                GS_THROW(GameSparks::RT::Proto::ProtocolBufferException("Invalid field id: 0, something went wrong in the stream"));
            default:
                GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::SkipKey(stream, key));
                break;
        }
    }

    assert(instance.OpCode != std::numeric_limits<int>::lowest());
    return {};
}


}}} /* namespace GameSparks.RT.Proto */
