#ifndef _SYSTEM_NET_SOCKETS_NETWORKSTREAM_HPP_
#define _SYSTEM_NET_SOCKETS_NETWORKSTREAM_HPP_

#include <vector>
#include "Socket.hpp"
#include "../../IO/Stream.hpp"

namespace System { namespace Net { namespace Sockets {

    class NetworkStream  : public IO::Stream
    {
        public:
            NetworkStream(Socket& socket);

            virtual Failable<void> Write(const System::Bytes &buffer, int offset, int size) override;

            virtual Failable<int> Read(System::Bytes &buffer, int offset, int count) override;

            virtual bool CanRead() const override;

            virtual bool CanWrite() const override;

        private:
                Socket& socket;
    };

}}}

#endif /* _SYSTEM_NET_SOCKETS_NETWORKSTREAM_HPP_ */
