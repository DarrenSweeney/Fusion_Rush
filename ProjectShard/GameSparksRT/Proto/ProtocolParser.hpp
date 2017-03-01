#ifndef _GAMESPARKSRT_PROTOCOLPARSER_HPP_
#define _GAMESPARKSRT_PROTOCOLPARSER_HPP_

#include <algorithm>
#include <string>
#include <vector>

#include "../../System/IO/Stream.hpp"
#include "../../System/IO/MemoryStream.hpp"
#include "../../System/Text/Encoding/UTF8.hpp"
#include "../../System/IO/IOException.hpp"
#include "../../System/String.hpp"
#include "./ProtocolBufferException.hpp"

namespace GameSparks { namespace RT { namespace Proto {

	enum class Wire
	{
		Varint = 0,          //int32, int64, UInt32, UInt64, SInt32, SInt64, bool, enum
		Fixed64 = 1,         //fixed64, sfixed64, double
		LengthDelimited = 2, //string, bytes, embedded messages, packed repeated fields
		Fixed32 = 5,         //32-bit    fixed32, SFixed32, float
	};

	class Key
	{
		public:
			const unsigned int Field;
			const Wire WireType;

			Key(unsigned int field, Wire wireType)
			:Field(field), WireType(wireType) { }

			std::string ToString() const
			{
				return "[Key: " + System::String::ToString(Field) + ", " + System::String::ToString(int(WireType)) + "]";
			}

		private:
	};

	class KeyValue
	{
		public:
			const class Key Key;
			const System::Bytes Value;

			KeyValue(const class Key& key, const System::Bytes& value)
			:Key(key)
			,Value(value) { }

			std::string ToString() const
			{
				return "[KeyValue: " + System::String::ToString(Key.Field) + ", " + System::String::ToString(int(Key.WireType)) + ", " + System::String::ToString(Value.size()) + " bytes]";
			}

		private:
	};

	class ProtocolParser
	{
		public:
		//internal static ObjectPool<System::IO::MemoryStream> Stack = PooledObjects.MemoryStreamPool;
        typedef unsigned char byte;
        typedef unsigned int uint;
        //typedef uint64_t uint64_t;
        typedef std::string string;
        typedef System::Bytes bytes;

        static System::Failable<Key> ReadKey(byte firstByte, System::IO::Stream& stream)
		{
			if (firstByte < 128)
				return Key((uint)(firstByte >> 3), (Wire)(firstByte & 0x07));
            GS_ASSIGN_OR_THROW(tmp, ReadUInt32(stream));
			uint fieldID = ((uint)tmp << 4) | ((uint)(firstByte >> 3) & 0x0F);
			return Key(fieldID, (Wire)(firstByte & 0x07));
		}

		/// <summary>
		/// Seek past the Value for the previously read key.
		/// </summary>
        static System::Failable<void> SkipKey(System::IO::Stream& stream, Key key)
		{
			switch (key.WireType)
			{
                case Wire::Fixed32:
                    GS_CALL_OR_THROW(stream.Seek(4, System::IO::SeekOrigin::Current));
                    return {};
                case Wire::Fixed64:
                    GS_CALL_OR_THROW(stream.Seek(8, System::IO::SeekOrigin::Current));
                    return {};
                case Wire::LengthDelimited:
                {
                    GS_ASSIGN_OR_THROW(offset, ProtocolParser::ReadUInt32(stream));
                    GS_CALL_OR_THROW(stream.Seek(offset, System::IO::SeekOrigin::Current));
                    return {};
                }
                case Wire::Varint:
                {
                    GS_CALL_OR_THROW(ProtocolParser::ReadSkipVarInt(stream));
                    return {};
                }
                default:
                {
                    GS_THROW(System::NotImplementedException("Unknown wire type: " + System::String::ToString(int(key.WireType))));
                }
			}
		}

        static System::Failable<string> ReadString(System::IO::Stream& stream)
        {
			//VarInt length
            GS_ASSIGN_OR_THROW(length, ReadUInt32(stream));

			System::IO::MemoryStream ms;// = PooledObjects.MemoryStreamPool.Pop ();

			bytes buffer(length);// = PooledObjects.ByteBufferPool.Pop ();

			uint read = 0;

			while (read < length) {
				GS_ASSIGN_OR_THROW(r, stream.Read(buffer, 0, std::min<int>(length - read, int(buffer.size()))));
                if (r == 0)
					return ::GameSparks::RT::Proto::ProtocolBufferException("Expected " + System::String::ToString(length - read) + " got " + System::String::ToString(read));
				GS_CALL_OR_THROW(ms.Write (buffer, 0, r));
				read += r;
			}

			string ret = System::Text::Encoding::UTF8::GetString(ms.GetBuffer(), 0, (int)ms.Position());

			//PooledObjects.ByteBufferPool.Push (buffer);
			//PooledObjects.MemoryStreamPool.Push (ms);
			return ret;
        }

        static System::Failable<void> WriteString(System::IO::Stream& stream, string val)
        {
            GS_CALL_OR_THROW(WriteBytes(stream, System::Text::Encoding::UTF8::GetBytes(val)));
            return {};
        }

        /// <summary>
        /// Writes length delimited byte array
        /// </summary>
        static System::Failable<void> WriteBytes(System::IO::Stream& stream, const bytes& val)
        {
            GS_CALL_OR_THROW(WriteUInt32(stream, (uint)val.size()));
            GS_CALL_OR_THROW(stream.Write(val, 0, int(val.size())));
            return {};
        }

		/// <summary>
		/// Writes length delimited byte array
		/// </summary>
		static System::Failable<void> WriteBytes(System::IO::Stream& stream, const bytes& val, int len)
		{
            GS_CALL_OR_THROW(WriteUInt32(stream, (uint)len));
			GS_CALL_OR_THROW(stream.Write(val, 0, len));
            return {};
		}


		/// <summary>
        /// Reads past a varint for an unknown field.
        /// </summary>
        static System::Failable<void> ReadSkipVarInt(System::IO::Stream& stream)
        {
			for (;;)
            {
                GS_ASSIGN_OR_THROW(b, stream.ReadByte());
                if (b < 0)
                    GS_THROW(System::IO::IOException("System::IO::Stream& ended too early"));

                if ((b & 0x80) == 0)
                    return {}; //end of varint
            }
        }

        /// <summary>
        /// Zig-zag signed VarInt format
        /// </summary>
        static System::Failable<int> ReadZInt32(System::IO::Stream& stream)
        {
            GS_ASSIGN_OR_THROW(val, ReadUInt32(stream));
            return (int)(val >> 1) ^ ((int)(val << 31) >> 31);
        }

        /// <summary>
        /// Zig-zag signed VarInt format
        /// </summary>
        static System::Failable<void> WriteZInt32(System::IO::Stream& stream, int val)
        {
            GS_CALL_OR_THROW(WriteUInt32(stream, (uint)((val << 1) ^ (val >> 31))));
            return {};
        }

        /// <summary>
        /// Unsigned VarInt format
        /// Do not use to read int32, use ReadUint64 for that.
        /// </summary>
        static System::Failable<uint> ReadUInt32(System::IO::Stream& stream)
        {
            uint val = 0;

            for (int n = 0; n < 5; n++)
            {
                GS_ASSIGN_OR_THROW(b, stream.ReadByte());
                if (b < 0)
                    GS_THROW(System::IO::IOException("System::IO::Stream& ended too early"));

                //Check that it fits in 32 bits
                if ((n == 4) && (b & 0xF0) != 0)
                    return ProtocolBufferException("Got larger VarInt than 32bit unsigned");
                //End of check

                if ((b & 0x80) == 0)
                    return val | (uint)b << (7 * n);

                val |= (uint)(b & 0x7F) << (7 * n);
            }

            return ProtocolBufferException("Got larger VarInt than 32bit unsigned");
        }

        /// <summary>
        /// Unsigned VarInt format
        /// </summary>
        static System::Failable<void> WriteUInt32(System::IO::Stream& stream, uint val)
        {
            byte b;
			for (;;)
            {
                b = (byte)(val & 0x7F);
                val = val >> 7;
                if (val == 0)
                {
                    GS_CALL_OR_THROW(stream.WriteByte(b));
                    break;
                }
                else
                {
                    b |= 0x80;
                    GS_CALL_OR_THROW(stream.WriteByte(b));
                }
            }
            return {};
        }

        /// <summary>
        /// Zig-zag signed VarInt format
        /// </summary>
        static System::Failable<int64_t> ReadZInt64(System::IO::Stream& stream)
        {
            GS_ASSIGN_OR_THROW(val, ReadUInt64(stream));
            // https://github.com/google/protobuf/blob/24fe6ba750bf8a247d41fc589460dce1bdd697a1/ruby/ext/google/protobuf_c/upb.h#L7703
            return (val >> 1) ^ -(int64_t)(val & 1);
        }

        /// <summary>
        /// Zig-zag signed VarInt format
        /// </summary>
        static System::Failable<void> WriteZInt64(System::IO::Stream& stream, int64_t val)
        {
            GS_CALL_OR_THROW(WriteUInt64(stream, (uint64_t)((val << 1) ^ (val >> 63))));
            return {};
        }

        /// <summary>
        /// Unsigned VarInt format
        /// </summary>
        static System::Failable<uint64_t> ReadUInt64(System::IO::Stream& stream)
        {
            uint64_t val = 0;

            for (int n = 0; n < 10; n++)
            {
                GS_ASSIGN_OR_THROW(b, stream.ReadByte());
                if (b < 0)
                    GS_THROW(System::IO::IOException("System::IO::Stream& ended too early"));

                //Check that it fits in 64 bits
                if ((n == 9) && (b & 0xFE) != 0)
                    return ProtocolBufferException("Got larger VarInt than 64 bit unsigned");
                //End of check

                if ((b & 0x80) == 0)
                    return val | (uint64_t)b << (7 * n);

                val |= (uint64_t)(b & 0x7F) << (7 * n);
            }

            return ProtocolBufferException("Got larger VarInt than 64 bit unsigned");
        }

        /// <summary>
        /// Unsigned VarInt format
        /// </summary>
        static System::Failable<void> WriteUInt64(System::IO::Stream& stream, uint64_t val)
        {
            byte b;
			for (;;)
            {
                b = (byte)(val & 0x7F);
                val = val >> 7;
                if (val == 0)
                {
                    GS_CALL_OR_THROW(stream.WriteByte(b));
                    break;
                }
                else
                {
                    b |= 0x80;
                    GS_CALL_OR_THROW(stream.WriteByte(b));
                }
            }
            return {};
        }

        static System::Failable<bool> ReadBool(System::IO::Stream& stream)
        {
            GS_ASSIGN_OR_THROW(b, stream.ReadByte());
            if (b < 0)
                GS_THROW(System::IO::IOException("System::IO::Stream& ended too early"));
            if (b == 1)
                return true;
            if (b == 0)
                return false;
            GS_THROW(ProtocolBufferException("Invalid boolean Value"));
        }

        static System::Failable<void> WriteBool(System::IO::Stream& stream, bool val)
        {
            GS_CALL_OR_THROW(stream.WriteByte(val ? (byte)1 : (byte)0));
            return {};
        }

		private:
	};

}}} /* namespace GameSparks.RT.Proto */

#endif /* _GAMESPARKSRT_PROTOCOLPARSER_HPP_ */
