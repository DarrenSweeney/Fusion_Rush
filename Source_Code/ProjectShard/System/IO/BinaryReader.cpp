#include "./BinaryReader.hpp"
#include "EndOfStreamException.hpp"
#include "../ArgumentException.hpp"
#include "../ArgumentOutOfRangeException.hpp"

namespace System { namespace IO {

        typedef unsigned int uint;

        BinaryReader::BinaryReader(Stream &stream_)
        :stream(stream_)
        ,_buffer(16)
        {
            if (!stream.CanRead())
            {
                assert(false);
                // GS_THROW(ArgumentException("ArgumentException"));
            }
        }

        BinaryReader::~BinaryReader() { }

        System::Failable<float> BinaryReader::ReadSingle() {
            GS_CALL_OR_THROW(FillBuffer(4));
            uint tmpBuffer = (uint)(_buffer[0] | _buffer[1] << 8 | _buffer[2] << 16 | _buffer[3] << 24);
            return *((float*)&tmpBuffer);
        }

        System::Failable<double> BinaryReader::ReadDouble() {
            GS_CALL_OR_THROW(FillBuffer(8));
            uint lo = (uint)(_buffer[0] | _buffer[1] << 8 |
                             _buffer[2] << 16 | _buffer[3] << 24);
            uint hi = (uint)(_buffer[4] | _buffer[5] << 8 |
                             _buffer[6] << 16 | _buffer[7] << 24);

            uint64_t tmpBuffer = ((uint64_t)hi) << 32 | lo;
            return *((double*)&tmpBuffer);
        }

        System::Failable<void> BinaryReader::FillBuffer(int numBytes) {
            if ((numBytes < 0 || numBytes > static_cast<int>(_buffer.size())))
            {
                GS_THROW(ArgumentOutOfRangeException("ArgumentOutOfRangeException"));
            }

            int bytesRead = 0;

            // Need to find a good threshold for calling ReadByte() repeatedly
            // vs. calling Read(byte[], int, int) for both buffered & unbuffered
            // streams.
            if (numBytes == 1)
            {
                GS_ASSIGN_OR_THROW(n, stream.ReadByte());
                if (n == -1)
                {
                    GS_THROW(EndOfStreamException("EndOfStreamException"));
                }

                _buffer[0] = (unsigned char)n;
                return {};
            }

            do
            {
                GS_ASSIGN_OR_THROW(n, stream.Read(_buffer, bytesRead, numBytes - bytesRead));
                if (n == 0)
                {
                    GS_THROW(EndOfStreamException("EndOfStreamException"));
                }
                bytesRead += n;
            } while (bytesRead < numBytes);

            return {};
        }
    }}
