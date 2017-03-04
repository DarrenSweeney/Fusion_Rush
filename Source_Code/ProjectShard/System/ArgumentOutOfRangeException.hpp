#ifndef _SYSTEM_ARGUMENTOUTOFRANGEEXCEPTION_HPP_INCLUDED_
#define _SYSTEM_ARGUMENTOUTOFRANGEEXCEPTION_HPP_INCLUDED_

#include "ArgumentException.hpp"

namespace System {

	class ArgumentOutOfRangeException : public ArgumentException
	{
		public:
			ArgumentOutOfRangeException(const std::string& message)
			:ArgumentException(message) {}
	};

} /* namespace System */

#endif /* _SYSTEM_ARGUMENTOUTOFRANGEEXCEPTION_HPP_INCLUDED_ */
