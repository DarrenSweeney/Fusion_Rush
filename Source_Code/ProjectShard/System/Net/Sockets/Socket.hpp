#ifndef _SYSTEM_NET_SOCKETS_SOCKET_HPP_
#define _SYSTEM_NET_SOCKETS_SOCKET_HPP_

#include "../../AsyncCallback.hpp"
#include "./AddressFamily.hpp"
#include "./SocketType.hpp"
#include "./ProtocolType.hpp"
#include "SocketOptionLevel.hpp"
#include "SocketOptionName.hpp"
#include <mbedtls/net.h>
#include "../IPEndPoint.hpp"
#include "../../Failable.hpp"
#include <System/Bytes.hpp>

#include <thread>

namespace System {class IAsyncResult;}

namespace System { namespace Net { namespace Sockets {

    class Socket
    {
        public:
            Socket(AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType);
            virtual ~Socket();

            void NoDelay(bool value);
            bool NoDelay() const;

            void SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, bool optionValue);

            void BeginConnect(
                    const IPEndPoint& endpoint,
                    const AsyncCallback& requestCallback
            );

            void BeginReceive(
                    System::Bytes& buffer,
                    const AsyncCallback& callback
            );
            // https://msdn.microsoft.com/en-us/library/w7wtt64b(v=vs.110).aspx
            int EndReceive(const System::IAsyncResult& res);

            Failable<int> Receive(System::Bytes &buffer);
            virtual Failable<int> Receive(System::Bytes &buffer, int offset, int count);

            bool Connected() const;

            virtual Failable<void> Send(const System::Bytes &buffer, int offset, int size);

            std::string LocalEndPoint = "TODO";

            void Poll();

        protected:
            virtual int internalRecv(unsigned char *buf, size_t len);
			virtual bool Connect(const IPEndPoint& endpoint);

            enum class State
            {
                CLOSED,
                CONNECTING,
                CONNECTED,
            };
            State state = State::CLOSED;
			mbedtls_net_context netCtx;
			volatile bool isTearingDown;
			AsyncCallback receiveCallback;
			System::Bytes* receiveBuffer = nullptr;

			std::thread connectThread; // for name resolution and connect()
			volatile bool isInsideInternalRecv;
			void teardown();
		private:
			void DoNoDelay(bool value);
			bool scheduleNoDelayFlag = false;
            ProtocolType protocolType;
    };

}}}

#endif /* _SYSTEM_NET_SOCKETS_SOCKET_HPP_ */
