#ifndef _SYSTEM_NET_IPENDPOINT_HPP_
#define _SYSTEM_NET_IPENDPOINT_HPP_

#include <string>

namespace System { namespace Net {

class IPEndPoint
{
    public:
        // this deviates from .NET, because mbed does connect via a hostname:port pair
        std::string Host;
        std::string Port;
        //IPAddress Address;
        //int Port = 0;
    private:
};

}}

#endif /* _SYSTEM_NET_IPENDPOINT_HPP_ */
