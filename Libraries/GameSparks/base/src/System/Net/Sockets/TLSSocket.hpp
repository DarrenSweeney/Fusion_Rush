#ifndef _SYSTEM_NET_TLSSOCKETS_SOCKET_HPP_
#define _SYSTEM_NET_TLSSOCKETS_SOCKET_HPP_

#include "./Socket.hpp"

#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>


namespace System { namespace Net { namespace Sockets {

	class TLSSocket : public Socket
	{
		public:
			TLSSocket(AddressFamily addressFamily);
			virtual ~TLSSocket() override;

			virtual Failable<int> Receive(System::Bytes &buffer, int offset, int count) override;
			virtual Failable<void> Send(const System::Bytes &buffer, int offset, int size) override;
		protected:
			virtual bool Connect(const IPEndPoint& endpoint) override;
			virtual int internalRecv(unsigned char *buf, size_t len) override;

			mbedtls_ssl_context ssl;
			mbedtls_ssl_config conf;
			mbedtls_entropy_context entropy;
			mbedtls_ctr_drbg_context ctr_drbg;
	};

}}}

#endif /* _SYSTEM_NET_TLSSOCKETS_SOCKET_HPP_ */
