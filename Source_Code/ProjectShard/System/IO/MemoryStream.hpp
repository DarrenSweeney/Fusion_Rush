#ifndef _SYSTEM_IO_MEMORYSTREAM_HPP_INCLUDED_
#define _SYSTEM_IO_MEMORYSTREAM_HPP_INCLUDED_

#include <vector>
#include <System/Bytes.hpp>
#include "Stream.hpp"

#ifdef max
#	undef max
#endif

namespace System { namespace IO {

    // https://github.com/dotnet/corefx/blob/ac67ffac987d0c27236c4a6cf1255c2bcbc7fe7d/src/System.IO/src/System/IO/MemoryStream.cs

	// A MemoryStream represents a Stream in memory (ie, it has no backing store).
	// This stream may reduce the need for temporary buffers and files in
	// an application.
	//
	// There are two ways to create a MemoryStream.  You can initialize one
	// from an unsigned byte array, or you can create an empty one.  Empty
	// memory streams are resizable, while ones created with a byte array provide
	// a stream "view" of the data.
	class MemoryStream : public Stream
	{
		public:
            /// Initializes a new instance of the MemoryStream class with an expandable capacity initialized as specified.
            MemoryStream(int capacity=0);
            ~MemoryStream();
            virtual bool CanRead () const override;
            virtual bool CanWrite() const override;
            virtual Failable<void> WriteByte(unsigned char value) override;
            virtual Failable<void> Write(const System::Bytes &buffer, int offset, int size) override;
            virtual Failable<int> ReadByte() override;
            virtual Failable<int> Read(System::Bytes &buffer, int offset, int count) override;
            virtual Failable<int64_t> Seek(int64_t offset, IO::SeekOrigin origin) override;
            virtual int Position() const override;
            virtual Failable<void> Position(const int pos) override;

            const Bytes& GetBuffer() const;

		private:
            void EnsureWriteable();
			Failable<bool> EnsureCapacity(int value);
            Failable<void> Capacity(int value);
            int Capacity() const;
            int64_t Length() const;

            Bytes _buffer;    // Either allocated internally or externally.
            int _origin=0;       // For user-provided arrays, start at this origin
            int _position=0;     // read/write head.
            int _length=0;       // Number of bytes within the memory stream
            int _capacity=0;     // length of usable portion of buffer for stream
               // Note that _capacity == _buffer.Length for non-user-provided byte[]'s

            bool _expandable=0;  // User-provided buffers aren't expandable.
            bool _writable=0;    // Can user write to this stream?
            //bool _exposable=0;   // Whether the array can be returned to the user.
            bool _isOpen=0;      // Is this stream open or closed?

            //static constexpr int MemStreamMaxLength = std::numeric_limits<int>::max();
			enum { MemStreamMaxLength = 0x7fffffff };
	};

}} /* namespace System.IO */

#endif /* _SYSTEM_IO_MEMORYSTREAM_HPP_INCLUDED_ */
