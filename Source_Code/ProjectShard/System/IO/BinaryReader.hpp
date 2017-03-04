#ifndef _SYSTEM_IO_BINARYREADER_HPP_
#define _SYSTEM_IO_BINARYREADER_HPP_

#include "Stream.hpp"

namespace System { namespace IO {

// https://github.com/dotnet/corefx/blob/ac67ffac987d0c27236c4a6cf1255c2bcbc7fe7d/src/System.IO/src/System/IO/BinaryReader.cs
class BinaryReader
{
    public:
        BinaryReader(Stream& stream);
        virtual ~BinaryReader();

        virtual System::Failable<float> ReadSingle();
        virtual System::Failable<double> ReadDouble();
    protected:
        System::Failable<void> FillBuffer(int numBytes);
    private:
        Stream& stream;
        Bytes _buffer;
};


}}

#endif /* _SYSTEM_IO_BINARYREADER_HPP_ */
