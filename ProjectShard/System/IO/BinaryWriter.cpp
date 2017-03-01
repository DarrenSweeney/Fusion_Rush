#include <iostream>
#include "./BinaryWriter.hpp"
#include "../ArgumentException.hpp"

namespace System { namespace IO {

        typedef unsigned char byte;
        typedef unsigned int uint;

        BinaryWriter::BinaryWriter(Stream &stream_)
        :stream(stream_)
        ,_buffer(16)
        {
            if (!stream.CanWrite())
            {
                std::clog << "cannot create a BinaryWriter for a stream that is not writable" << std::endl;
                assert(false);
            }
        }

        Failable<void> BinaryWriter::Write(float value) {
            if (!stream.CanWrite())
            {
                std::clog << "cannot create a BinaryWriter for a stream that is not writable" << std::endl;
                assert(false);
            }

            uint TmpValue = *(uint*)&value;
            _buffer[0] = (byte)TmpValue;
            _buffer[1] = (byte)(TmpValue >> 8);
            _buffer[2] = (byte)(TmpValue >> 16);
            _buffer[3] = (byte)(TmpValue >> 24);
            GS_CALL_OR_THROW(stream.Write(_buffer, 0, 4));
            return {};
        }

        Failable<void> BinaryWriter::Write(double value) {
            if (!stream.CanWrite())
            {
                std::clog << "cannot create a BinaryWriter for a stream that is not writable" << std::endl;
                assert(false);
            }

            uint64_t TmpValue = *(uint64_t*)&value;
            _buffer[0] = (byte)TmpValue;
            _buffer[1] = (byte)(TmpValue >> 8);
            _buffer[2] = (byte)(TmpValue >> 16);
            _buffer[3] = (byte)(TmpValue >> 24);
            _buffer[4] = (byte)(TmpValue >> 32);
            _buffer[5] = (byte)(TmpValue >> 40);
            _buffer[6] = (byte)(TmpValue >> 48);
            _buffer[7] = (byte)(TmpValue >> 56);
            GS_CALL_OR_THROW(stream.Write(_buffer, 0, 8));
            return {};
        }
}} /* namespace System.IO */
