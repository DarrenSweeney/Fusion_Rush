#ifndef _SYSTEM_OBJECTDISPOSEDEXCEPTION_HPP_INCLUDED_
#define _SYSTEM_OBJECTDISPOSEDEXCEPTION_HPP_INCLUDED_

#include "./InvalidOperationException.hpp"

namespace System {

	class ObjectDisposedException : public InvalidOperationException
	{
		public: ObjectDisposedException(const std::string what) : InvalidOperationException(what, "System.ObjectDisposedException") {}
	};

} /* namespace System */

#endif /* _SYSTEM_OBJECTDISPOSEDEXCEPTION_HPP_INCLUDED_ */
