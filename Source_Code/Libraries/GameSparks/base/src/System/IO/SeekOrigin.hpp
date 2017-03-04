#ifndef _SYSTEM_IO_SEEKORIGIN_HPP_INCLUDED_
#define _SYSTEM_IO_SEEKORIGIN_HPP_INCLUDED_

namespace System { namespace IO {

	enum class SeekOrigin
	{
		Begin,   ///Specifies the beginning of a stream.
		Current, ///Specifies the current position within a stream.
		End      ///Specifies the end of a stream.
	};

}} /* namespace System.IO */

#endif /* _SYSTEM_IO_SEEKORIGIN_HPP_INCLUDED_ */
