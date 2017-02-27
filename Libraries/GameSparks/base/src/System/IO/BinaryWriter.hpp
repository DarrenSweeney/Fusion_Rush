#ifndef _SYSTEM_IO_BINARYWRITER_HPP_INCLUDED_
#define _SYSTEM_IO_BINARYWRITER_HPP_INCLUDED_

#include "Stream.hpp"

namespace System { namespace IO {

	class BinaryWriter
	{
		public:
			BinaryWriter(Stream& stream);
			Failable<void> Write(float);
			Failable<void> Write(double);
		private:
			Stream& stream;
			Bytes _buffer;
	};

}} /* namespace System.IO */

#endif /* _SYSTEM_IO_BINARYWRITER_HPP_INCLUDED_ */
