#ifndef _SYSTEM_ASYNCCALLBACK_HPP_
#define _SYSTEM_ASYNCCALLBACK_HPP_

#include <functional>
#include "IAsyncResult.hpp"

namespace System {

    typedef std::function<void (const IAsyncResult& ar)> AsyncCallback;

}

#endif /* _SYSTEM_ASYNCCALLBACK_HPP_ */
