#include "./RTData.Serializer.hpp"
#include "ProtocolParser.hpp"
#include "ReusableBinaryWriter.hpp"
#include "./ProtocolBufferException.hpp"
#include "GameSparksRT/Proto/RTVal.hpp"
#include "../../System/IO/EndOfStreamException.hpp"
#include <GameSparksRT/RTData.hpp>

typedef unsigned char byte;

namespace GameSparks { namespace RT { namespace Proto {


System::Failable<void> RTValSerializer::ReadRTVal (System::IO::Stream& stream, System::IO::BinaryReader& br, RTVal& instance)
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
                return ::GameSparks::RT::Proto::ProtocolBufferException("Read past max limit");
        }
        GS_ASSIGN_OR_THROW(keyByte, stream.ReadByte());
        if (keyByte == -1)
            GS_THROW(System::IO::EndOfStreamException("EndOfStreamException"));
        // Optimized reading of known fields with field ID < 16
        switch (keyByte)
        {
            // Field 1 LengthDelimited
            case 10:
            {
                GS_ASSIGN_OR_THROW(tmp, ::GameSparks::RT::Proto::ProtocolParser::ReadString(stream));
                instance.string_val = tmp;
                continue;
            }
            // Field 2 LengthDelimited
            case 18:{
                // repeated packed
                GS_ASSIGN_OR_THROW(end2_, ::GameSparks::RT::Proto::ProtocolParser::ReadUInt32 (stream));
                int end2 = static_cast<int>(end2_);
                end2 += stream.Position();
                RTVector v;
                int i = 0;
                while (stream.Position() < end2) {
                    GS_ASSIGN_OR_THROW(read, br.ReadSingle ());
                    switch (i) {
                        case 0:
                            v.x = read;
                            break;
                        case 1:
                            v.y = read;
                            break;
                        case 2:
                            v.z = read;
                            break;
                        case 3:
                            v.w = read;
                            break;
                        default:
                            break;
                    }
                    i++;
                }
                instance.vec_val = v;

                if (stream.Position() != end2)
                    return ::GameSparks::RT::Proto::ProtocolBufferException("Read too many bytes in packed data");
                continue;}
                // Field 14 LengthDelimited
            case 114:
            {
                if (!instance.data_val.HasValue()) {
                    instance.data_val = RTData();
                }
                GS_CALL_OR_THROW(RTData::ReadRTData(stream, br, instance.data_val.Value()));
                continue;
            }
        }

        GS_ASSIGN_OR_THROW(key, ::GameSparks::RT::Proto::ProtocolParser::ReadKey((unsigned char)keyByte, stream));

        // Reading field ID > 16 and unknown field ID/wire type combinations
        switch (key.Field)
        {
            case 0:
                return ::GameSparks::RT::Proto::ProtocolBufferException("Invalid field id: 0, something went wrong in the stream");
            default:
                GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::SkipKey(stream, key));
                break;
        }
    }
    return {};
}


System::Failable<void> RTValSerializer::WriteRTVal (System::IO::Stream& stream, const RTVal& val)
{
    BinaryWriteMemoryStream ms;
    if (val.string_val.HasValue())
    {
        // Key for field: 1, LengthDelimited
        GS_CALL_OR_THROW(ms.WriteByte(10));
        GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteBytes(ms, System::Text::Encoding::UTF8::GetBytes(val.string_val.Value())));
    }
    else if(val.data_val.HasValue())
    {
        GS_CALL_OR_THROW(ms.WriteByte(114));
        GS_CALL_OR_THROW(RTData::WriteRTData(ms, val.data_val.Value()));
    }
    else if (val.vec_val.HasValue())
    {

        RTVector vec_value = val.vec_val.Value();
        // Key for field: 2, LengthDelimited
        GS_CALL_OR_THROW(ms.WriteByte(18));

        /*!
         * You need to set x, xy, xyz or xyzw. You cannot leave dimensions of the vector blank.
         * For example you cannot only set y and leave the rest unset.
         * */
        assert(
            ((vec_value.x.HasValue() && vec_value.y.HasValue() && vec_value.z.HasValue() && vec_value.w.HasValue()) ||
            (vec_value.x.HasValue() && vec_value.y.HasValue() && vec_value.z.HasValue()) ||
            (vec_value.x.HasValue() && vec_value.y.HasValue()) ||
            (vec_value.x.HasValue())) && "RTVector cannot be sparse."
        );

        int numberOfFloatsSet = vec_value.w.HasValue() ? 4 : (vec_value.z.HasValue() ? 3 : (vec_value.y.HasValue() ? 2 : (vec_value.x.HasValue() ? 1 : 0)));
        GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteUInt32(ms, 4u * (uint)numberOfFloatsSet));

        for(int i=0 ; i<numberOfFloatsSet ; i++)
        {
            switch (i)
            {
                case 0:
                    GS_CALL_OR_THROW(ms.BinaryWriter.Write(vec_value.x.Value()));
                    break;
                case 1:
                    GS_CALL_OR_THROW(ms.BinaryWriter.Write(vec_value.y.Value()));
                    break;
                case 2:
                    GS_CALL_OR_THROW(ms.BinaryWriter.Write(vec_value.z.Value()));
                    break;
                case 3:
                    GS_CALL_OR_THROW(ms.BinaryWriter.Write(vec_value.w.Value()));
                    break;
                default:
                    break;
            }
        }

    }

    auto data = ms.GetBuffer();
    GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteUInt32(stream, (uint)ms.Position()));
    GS_CALL_OR_THROW(stream.Write(data, 0, (int)ms.Position()));

    return {};
}


System::Failable<void> RTDataSerializer::ReadRTData(System::IO::Stream& stream, System::IO::BinaryReader& br, RTData& instance){
    //BinaryReader br = ((PositionStream)stream).BinaryReader;

    GS_ASSIGN_OR_THROW(limit_, ::GameSparks::RT::Proto::ProtocolParser::ReadUInt32(stream))
    int limit = static_cast<int>(limit_);
    limit += stream.Position();
	for (;;)
    {
        if (stream.Position() >= limit)
        {
            if (stream.Position() == limit)
                break;
            else
                return ::GameSparks::RT::Proto::ProtocolBufferException("Read past max limit");
        }

        GS_ASSIGN_OR_THROW(keyByte, stream.ReadByte());

        if (keyByte == -1)
            break;

        GS_ASSIGN_OR_THROW(key, ::GameSparks::RT::Proto::ProtocolParser::ReadKey((unsigned char)keyByte, stream));

        /*if (key.Field == 0) {
            GS_THROW(::GameSparks::RT::Proto::ProtocolBufferException("Invalid field id: 0, something went wrong in the stream"));
        }*/

        if (key.Field >= GameSparksRT::MAX_RTDATA_SLOTS) {
            GS_THROW(::GameSparks::RT::Proto::ProtocolBufferException("Invalid field id: to many RTData fields"));
        }

        switch (key.WireType) {
            case Wire::Varint:
            {
                GS_ASSIGN_OR_THROW(tmp, ProtocolParser::ReadZInt64 (stream));
                instance.data.at(key.Field) = RTVal(tmp);
                break;
            }
            case Wire::Fixed32:
            {
                GS_ASSIGN_OR_THROW(tmp, br.ReadSingle ());
                instance.data.at(key.Field) = tmp;
                break;
            }
            case Wire::Fixed64:
            {
                GS_ASSIGN_OR_THROW(tmp, br.ReadDouble ());
                instance.data.at(key.Field) = tmp;
                break;
            }
            case Wire::LengthDelimited:
                GS_CALL_OR_THROW(RTVal::DeserializeLengthDelimited (stream, br, instance.data.at(key.Field)));
                break;
            default:
                break;
        }

        // Reading field ID > 16 and unknown field ID/wire type combinations
        switch (key.Field)
        {
            case 0:
                return ::GameSparks::RT::Proto::ProtocolBufferException("Invalid field id: 0, something went wrong in the stream");
            default:
                break;
        }
    }
    return {};
}


System::Failable<void> RTDataSerializer::WriteRTData(System::IO::Stream& stream, const RTData& instance)
{
    BinaryWriteMemoryStream ms;

    for (ProtocolParser::uint index = 1; index < ProtocolParser::uint(instance.data.size()); index++) {

        RTVal entry = instance.data [index];

        if (entry.long_val.HasValue()) {
            GS_CALL_OR_THROW(ProtocolParser::WriteUInt32 (ms, index << 3));
            //ms.WriteByte ((byte)(index << 3));
            GS_CALL_OR_THROW(ProtocolParser::WriteZInt64 (ms, (int64_t)entry.long_val.Value()));
        } else if (entry.double_val.HasValue()) {
            GS_CALL_OR_THROW(ProtocolParser::WriteUInt32 (ms, (index << 3) | ((uint)1)));
            //ms.WriteByte ((byte)((index << 3) + 1));
            GS_CALL_OR_THROW(ms.BinaryWriter.Write ((double)entry.double_val.Value()));
        } else if (entry.float_val.HasValue()) {
            GS_CALL_OR_THROW(ProtocolParser::WriteUInt32 (ms, (index << 3) | ((uint)5)));
            //ms.WriteByte ((byte)((index << 3) + 5));
            GS_CALL_OR_THROW(ms.BinaryWriter.Write ((float)entry.float_val.Value()));

        } else if (entry.data_val.HasValue() || entry.string_val.HasValue() || entry.vec_val.HasValue()) {
            GS_CALL_OR_THROW(ProtocolParser::WriteUInt32 (ms, (index << 3) | ((uint)2)));
            //ms.WriteByte ((byte)((index << 3) + 2));
            GS_CALL_OR_THROW(entry.SerializeLengthDelimited (ms));
        }
    }

    auto buffer = ms.GetBuffer();

    GS_CALL_OR_THROW(::GameSparks::RT::Proto::ProtocolParser::WriteUInt32(stream, (uint)ms.Position()));
    GS_CALL_OR_THROW(stream.Write(buffer, 0, (int)ms.Position()));

    return {};
}


}}} /* namespace GameSparks.RT.Proto */

