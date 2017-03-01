#include "Stream.hpp"

namespace System { namespace IO {

Failable<void> Stream::WriteByte(unsigned char value) {
    Bytes oneByteArray(1, value);
    oneByteArray[0] = value;
    GS_CALL_OR_THROW(Write(oneByteArray, 0, 1));
    return {};
}

Failable<int> Stream::ReadByte() {
    Bytes oneByteArray(1);
    GS_ASSIGN_OR_THROW(r, Read(oneByteArray, 0, 1));
    if (r == 0)
    {
        return -1;
    }
    return oneByteArray[0];
}

}}
