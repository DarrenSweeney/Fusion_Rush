#ifndef _SYSTEM_THREADING_THREAD_HPP_INCLUDED_
#define _SYSTEM_THREADING_THREAD_HPP_INCLUDED_

#include <string>

namespace System { namespace Threading {

	class Thread
	{
		public:
		    static void SetName(std::string name);
			static std::string GetName();
		protected:

		private:
	};

}} /* namespace System.Threading */

#endif /* _SYSTEM_THREADING_THREAD_HPP_INCLUDED_ */
