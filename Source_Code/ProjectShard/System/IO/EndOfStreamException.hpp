#ifndef _SYSTEM_IO_ENDOFSTREAMEXCEPTION_HPP_INCLUDED_
#define _SYSTEM_IO_ENDOFSTREAMEXCEPTION_HPP_INCLUDED_

#include "../Exception.hpp"

namespace System { namespace IO {

	class EndOfStreamException : public Exception
	{
		public: EndOfStreamException(const std::string what) : Exception(what, "EndOfStreamException") {}
	};

}} /* namespace System.IO */

#endif /* _SYSTEM_IO_ENDOFSTREAMEXCEPTION_HPP_INCLUDED_ */
