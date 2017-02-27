#ifndef _SYSTEM_NET_SOCKETS_TCPCLIENT_HPP_
#define _SYSTEM_NET_SOCKETS_TCPCLIENT_HPP_

#include "./AddressFamily.hpp"
#include "./TLSSocket.hpp"
#include "./NetworkStream.hpp"

namespace System { namespace Net { namespace Sockets {

	/// Note: the TcpClient is using the TLSSocket!
    class TcpClient
    {
        public:
            TcpClient(AddressFamily addressFamily);

            void NoDelay(bool value);
            bool NoDelay() const;

            bool Connected() const;
            void Close();

            NetworkStream& GetStream();

            Socket& Client();

            void BeginConnect(const IPEndPoint& endpoint, const AsyncCallback& requestCallback);

            void Poll();
        private:
            TLSSocket client;
            NetworkStream networkStream;
    };

}}}

#endif /* _SYSTEM_NET_SOCKETS_TCPCLIENT_HPP_ */
