#include "./TLSSocket.hpp"

#include <mbedtls/error.h>
#include <mbedtls/platform.h>
#include "../../ObjectDisposedException.hpp"

namespace System { namespace Net { namespace Sockets {
	TLSSocket::TLSSocket(AddressFamily addressFamily)
		:Socket(addressFamily, SocketType::Stream, ProtocolType::Tcp)
	{
		//mbedtls_debug_set_threshold( 1000 );
		mbedtls_ssl_init(&ssl);
		mbedtls_ssl_config_init(&conf);

		//mbedtls_x509_crt_init( &cacert );
		mbedtls_ctr_drbg_init(&ctr_drbg);
		mbedtls_entropy_init(&entropy);
	}


	TLSSocket::~TLSSocket()
	{
		teardown();
		//mbedtls_x509_crt_free( &cacert );
		mbedtls_ssl_free(&ssl);
		mbedtls_ssl_config_free(&conf);
		mbedtls_ctr_drbg_free(&ctr_drbg);
		mbedtls_entropy_free(&entropy);
	}

	static void set_errstr(const std::string& e)
	{
		std::cerr << "TLS socket Error: " << e << std::endl;
	}

	static std::string mbedtls_error_to_string_2(int result)
	{
		assert(result < 0); // you cannot translate an error that is none.

		char buf[256];
		mbedtls_strerror(result, buf, sizeof(buf));
		return buf;
	}

	static void set_errstr(int res)
	{
		set_errstr(mbedtls_error_to_string_2(res));
	}

	static void debug_print(void *ctx, int level, const char *file, int line, const char *str)
	{
		((void)level);
		mbedtls_fprintf((FILE *)ctx, "%s:%04d: %s", file, line, str);
		//fflush((FILE *)ctx);
	}

	bool TLSSocket::Connect(const IPEndPoint& endpoint)
	{
		if(Connected())
			return true;

		if (!Socket::Connect(endpoint))
			return false;

		state = State::CONNECTING;

		int res = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, nullptr, 0);
		res = mbedtls_ssl_config_defaults(&conf,
			MBEDTLS_SSL_IS_CLIENT,
			MBEDTLS_SSL_TRANSPORT_STREAM,
			MBEDTLS_SSL_PRESET_DEFAULT);

		if (res != 0)
		{
			set_errstr(res);
			state = State::CLOSED;
			return false;
		}


		// default suite, but with at least TLS 1.2
		mbedtls_ssl_conf_min_version(&conf, MBEDTLS_SSL_MAJOR_VERSION_3, MBEDTLS_SSL_MINOR_VERSION_3);

		/* OPTIONAL is not optimal for security,
		* but makes interop easier in this simplified example */
		//mbedtls_ssl_conf_authmode(&conf, MBEDTLS_SSL_VERIFY_REQUIRED);
		mbedtls_ssl_conf_authmode(&conf, MBEDTLS_SSL_VERIFY_NONE);

		//ret = mbedtls_x509_crt_parse( &cacert, (const unsigned char *) mbedtls_test_cas_pem, mbedtls_test_cas_pem_len );
		//mbedtls_ssl_conf_ca_chain( &conf, &cacert, NULL );

		mbedtls_ssl_conf_rng(&conf, mbedtls_ctr_drbg_random, &ctr_drbg);
		mbedtls_ssl_conf_dbg(&conf, debug_print, stderr);

		res = mbedtls_ssl_setup(&ssl, &conf);
		if (res != 0)
		{
			set_errstr(res);
			state = State::CLOSED;
			return false;
		}

		res = mbedtls_ssl_set_hostname(&ssl, endpoint.Host.c_str());
		if (res != 0)
		{
			set_errstr(res);
			state = State::CLOSED;
			return false;
		}

		mbedtls_ssl_set_bio(&ssl, &netCtx, mbedtls_net_send, mbedtls_net_recv, 0);// , mbedtls_net_recv_timeout);

		do res = mbedtls_ssl_handshake(&ssl);
		while (res == MBEDTLS_ERR_SSL_WANT_READ || res == MBEDTLS_ERR_SSL_WANT_WRITE);

		if (res != 0)
		{
			set_errstr(res);
			state = State::CLOSED;
			return false;
		}

		uint32_t flags;
		if ((flags = mbedtls_ssl_get_verify_result(&ssl)) != 0)
		{
			char vrfy_buf[512];
			mbedtls_x509_crt_verify_info(vrfy_buf, sizeof(vrfy_buf), "  ! ", flags);
			set_errstr(vrfy_buf);
			state = State::CLOSED;
			return false;
		}

		state = State::CONNECTED;
		return true;
	}


	Failable<int> TLSSocket::Receive(System::Bytes &buffer, int offset, int count)
	{
		if (isTearingDown)
			GS_THROW(System::ObjectDisposedException("Socket has closed or read error!"));

		assert(Connected());
		assert(static_cast<int>(buffer.size()) >= offset + count);

		auto set_blocking_result = mbedtls_net_set_block(&netCtx);
		(void)set_blocking_result;
		assert(set_blocking_result >= 0);

		assert(!this->receiveCallback); // you can't do a blocking read, while you have a non blocking read scheduled
		assert(!this->receiveBuffer);

		int result = 0;
		do result = mbedtls_ssl_read(&ssl, buffer.data() + offset, count);
		while (result == MBEDTLS_ERR_SSL_WANT_READ || result == MBEDTLS_ERR_SSL_WANT_WRITE);

		if (result < 0)
		{
			GS_THROW(System::ObjectDisposedException("Socket has closed or read error:" + std::string(mbedtls_error_to_string_2(result))));
		}
		if (result == 0)
		{
			GS_THROW(System::ObjectDisposedException("Socket has closed or read error: Zero bytes"));
		}
		return result;
	}


	Failable<void> TLSSocket::Send(const System::Bytes &buffer, int offset, int size)
	{
		int ret = 0;
		do ret = mbedtls_ssl_write(&ssl, buffer.data() + offset, size);
		while (ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE);
		//if (ret < 0) set_errstr(ret);

		if (ret < 0)
		{
			GS_THROW(ObjectDisposedException("Socket has closed or read error:" + std::string(mbedtls_error_to_string_2(ret))));
		}
		return{};
	}


	int TLSSocket::internalRecv(unsigned char *, size_t)
	{
		assert(false); // UDP Only
		return 0;
	}


}}}
