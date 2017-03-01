#ifndef _SYSTEM_ARGUMENTEXCEPTION_HPP_INCLUDED_
#define _SYSTEM_ARGUMENTEXCEPTION_HPP_INCLUDED_

#include "Exception.hpp"

namespace System {

	class ArgumentException : public Exception
	{
		public: ArgumentException(const std::string& what) : Exception(what, "ArgumentException") {}
	};

} /* namespace System */

#endif /* _SYSTEM_ARGUMENTEXCEPTION_HPP_INCLUDED_ */
