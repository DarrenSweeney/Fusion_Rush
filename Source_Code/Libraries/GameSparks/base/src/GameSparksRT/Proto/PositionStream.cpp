#include <assert.h>
#include "./PositionStream.hpp"

namespace GameSparks { namespace RT {

System::Failable<int> PositionStream::Read(System::Bytes& buffer, int offset, int count)
{
    GS_ASSIGN_OR_THROW(read, stream.Read(buffer, offset, count));
    assert(read >= 0);
    BytesRead += read;
    return read;
}

System::Failable<int> PositionStream::ReadByte()
{
    System::Bytes readByte(1);
    GS_ASSIGN_OR_THROW(read, Read (readByte, 0, 1));

    if (read == 1) {
        return readByte [0];
    }
    return -1;
}

int PositionStream::Position() const {
    return BytesRead;
}

bool PositionStream::CanRead() const {
    return true;
}

}} /* namespace GameSparks.RT */
