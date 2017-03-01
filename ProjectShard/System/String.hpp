#ifndef _SYSTEM_STRING_HPP_INCLUDED_
#define _SYSTEM_STRING_HPP_INCLUDED_

#include <string>
#include <sstream>
#include <iomanip>

namespace System {

	class String
	{
		public:

		template <typename T>
		static std::string ToString(const T& o)
        {
            std::stringstream stream;
            stream << std::boolalpha;
            stream << o;
            return stream.str();
        }
	};

} /* namespace System */

#endif /* _SYSTEM_STRING_HPP_INCLUDED_ */
