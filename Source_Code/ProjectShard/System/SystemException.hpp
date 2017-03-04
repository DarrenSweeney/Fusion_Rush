#ifndef _SYSTEM_SYSTEMEXCEPTION_HPP_INCLUDED_
#define _SYSTEM_SYSTEMEXCEPTION_HPP_INCLUDED_

#include "Exception.hpp"

namespace System {

	class SystemException : public Exception
	{
		public: SystemException(const std::string what) : Exception(what, "System.SystemException") {}
		public: SystemException(const std::string what, const std::string typeName) : Exception(what, typeName) {}
	};

} /* namespace System */

#endif /* _SYSTEM_SYSTEMEXCEPTION_HPP_INCLUDED_ */
