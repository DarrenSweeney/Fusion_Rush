#ifndef _SYSTEM_IO_IOEXCEPTION_HPP_INCLUDED_
#define _SYSTEM_IO_IOEXCEPTION_HPP_INCLUDED_

#include "../SystemException.hpp"

namespace System { namespace IO {

	class IOException : public SystemException
	{
		public: IOException(const std::string what) : SystemException(what, "System.IO.IOException") {}
	};

}} /* namespace System.IO */

#endif /* _SYSTEM_IO_IOEXCEPTION_HPP_INCLUDED_ */
