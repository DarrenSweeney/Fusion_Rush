#ifndef _SYSTEM_INVALIDOPERATIONEXCEPTION_HPP_INCLUDED_
#define _SYSTEM_INVALIDOPERATIONEXCEPTION_HPP_INCLUDED_

#include "SystemException.hpp"

namespace System {

	class InvalidOperationException : public SystemException
	{
		public: InvalidOperationException(const std::string what) : SystemException(what, "System.InvalidOperationException") {}
		public: InvalidOperationException(const std::string what, const std::string typeName) : SystemException(what, typeName) {}
	};

} /* namespace System */

#endif /* _SYSTEM_INVALIDOPERATIONEXCEPTION_HPP_INCLUDED_ */
