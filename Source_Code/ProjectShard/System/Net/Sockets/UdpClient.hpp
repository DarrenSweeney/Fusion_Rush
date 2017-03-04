#ifndef _SYSTEM_NET_SOCKETS_UDPCLIENT_HPP_INCLUDED_
#define _SYSTEM_NET_SOCKETS_UDPCLIENT_HPP_INCLUDED_

#include "Socket.hpp"

namespace System { namespace Net { namespace Sockets {

	class UdpClient
	{
		public:
			UdpClient();

			void EnableBroadcast(bool value);
			void ExclusiveAddressUse(bool value);
			void MulticastLoopback(bool value);

			Socket& Client();
			void BeginConnect(const IPEndPoint& endpoint, const AsyncCallback& requestCallback);
			//void Connect(const IPEndPoint& endpoint);

			Failable<void> Send(const Bytes& dgram, int bytes);
		protected:

		private:
			Socket client;
	};

}}} /* namespace System.Net.Sockets */

#endif /* _SYSTEM_NET_SOCKETS_UDPCLIENT_HPP_INCLUDED_ */
