#if defined(_MSC_VER)
#	pragma warning(error: 4005)
#	pragma warning(disable: 4127)
#endif

#define MBEDTLS_AMALGAMATE
#define MBEDTLS_UNREAL
#include "./mbedtls/net.c"
#undef inline

#ifdef read
#	undef read
#endif

#ifdef write
#	undef write
#endif

#ifdef close
#	undef close
#endif

#undef MBEDTLS_UNREAL

#if 1
extern "C"
{
static void mbedtls_zeroize(void *v, size_t n) {
	volatile unsigned char *p = (unsigned char *)v; while (n--) *p++ = 0;
}

#define P P_blowfish
#include "mbedtls/blowfish.c"
#undef P
#include "mbedtls/entropy.c"
#include "mbedtls/entropy_poll.c"
#include "mbedtls/md5.c"
#undef P
#include "mbedtls/sha1.c"
#undef R
#undef P
#define K K_256
#include "mbedtls/sha256.c"
#undef F1
#undef K
#undef SHR
#undef ROTR
#undef S0
#undef S
#undef S1
#undef S2
#undef S3
#define K K_512
#include "mbedtls/sha512.c"
#undef F1
#undef K
#undef SHR
#undef ROTR
#undef S0
#undef S
#undef S1
#undef S2
#undef S3
#undef P
#include "mbedtls/ripemd160.c"
#include "mbedtls/ctr_drbg.c"
#include "mbedtls/x509.c"
#include "mbedtls/x509_crt.c"
#include "mbedtls/ssl_tls.c"
#undef inline
#include "mbedtls/ssl_cli.c"
#undef inline
	//#include "mbedtls/ssl_srv.c"
#define supported_init supported_init_ssl_ciphersuites
#include "mbedtls/ssl_ciphersuites.c"
#undef supported_init
#define FSb FSb_aes
#include "mbedtls/aes.c"
#include "mbedtls/aesni.c"
#include "mbedtls/padlock.c"
#undef FSb
#include "mbedtls/bignum.c"
#undef asm
#include "mbedtls/ecp.c"
#undef inline
#include "mbedtls/ecp_curves.c"
#undef inline
#include "mbedtls/md.c"
#undef P
#include "mbedtls/md_wrap.c"
#include "mbedtls/rsa.c"
#include "mbedtls/pk.c"
#include "mbedtls/pkcs5.c"
#include "mbedtls/pkparse.c"
#include "mbedtls/pk_wrap.c"
#define supported_init supported_init_cipher
#include "mbedtls/cipher.c"
#undef supported_init
#include "mbedtls/cipher_wrap.c"
#include "mbedtls/asn1parse.c"
#include "mbedtls/asn1write.c"
#include "mbedtls/dhm.c"
#include "mbedtls/ecdh.c"
#include "mbedtls/debug.c"
#undef inline
#include "mbedtls/oid.c"
#include "mbedtls/pem.c"
#include "mbedtls/gcm.c"
#include "mbedtls/ccm.c"
#include "mbedtls/platform.c"
#include "mbedtls/certs.c"
#include "mbedtls/des.c"
#include "mbedtls/error.c"
#include "mbedtls/timing.c"
#undef asm
#include "mbedtls/arc4.c"
#define FSb FSb_camellia
#include "mbedtls/camellia.c"
#undef ROTL
#include "mbedtls/ecdsa.c"
#include "mbedtls/pkcs12.c"
#include "mbedtls/base64.c"
#include "mbedtls/hmac_drbg.c"

#undef R
#undef P
#undef S
}
#endif

#define UI GET_OF_MY_LAWN

// silence warnings on windows

#if defined(_MSC_VER)
#	if !defined(_CRT_SECURE_NO_WARNINGS)
#		define _CRT_SECURE_NO_WARNINGS
#	endif
#	if !defined(_CRT_SECURE_NO_DEPRECATE)
#		define _CRT_SECURE_NO_DEPRECATE
#	endif
#endif

//dependencies
#if defined(WIN32)
#	ifdef _MSC_VER
#		include <eh.h>
#	endif
#else 
# 	define _CRTIMP __declspec(dllimport) _CRTIMP bool __cdecl __uncaught_exception();
#endif

#include "easywsclient/easywsclient.cpp"
#include "google/timesupport.cpp"
#include "google/strptime.cpp"

#include "cjson/cJSON.cpp"

#include "GameSparks/GS.cpp"
#include "GameSparks/GSConnection.cpp"
#include "GameSparks/GSData.cpp"
#include "GameSparks/GSDateTime.cpp"
#include "GameSparks/GSMessage.cpp"
#include "GameSparks/GSRequest.cpp"
#include "GameSparks/GSUtil.cpp"
#include "GameSparks/IGSPlatform.cpp"

// sources for the RT SDK
#if !defined(GS_NO_RT_SDK)
#	define GS_NO_RT_SDK 0
#endif

#if !GS_NO_RT_SDK

#if !(__cplusplus >= 201103L || _MSC_VER >= 1800 )
#	error "The RT SDK requires C++11 support. Please update your compiler settings or define GS_NO_RT_SDK=1 to disable the RT SDK."
#endif

#	include "GameSparksRT/Commands/ActionCommand.cpp"
#	include "GameSparksRT/Commands/CommandFactory.cpp"
#	include "GameSparksRT/Commands/CustomCommand.cpp"
#	include "GameSparksRT/Commands/LogCommand.cpp"
#	include "GameSparksRT/Commands/Requests/CustomRequest.cpp"
#	include "GameSparksRT/Commands/Requests/LoginCommand.cpp"
#	include "GameSparksRT/Commands/Requests/PingCommand.cpp"
#	include "GameSparksRT/Commands/Results/LoginResult.cpp"
#	include "GameSparksRT/Commands/Results/PingResult.cpp"
#	include "GameSparksRT/Commands/Results/PlayerConnectMessage.cpp"
#	include "GameSparksRT/Commands/Results/PlayerDisconnectMessage.cpp"
#	include "GameSparksRT/Commands/Results/UDPConnectMessage.cpp"
#	include "GameSparksRT/Connection/Connection.cpp"
#	include "GameSparksRT/Connection/FastConnection.cpp"
#	include "GameSparksRT/Connection/ReliableConnection.cpp"
#	include "GameSparksRT/GameSparksRT.cpp"
#	include "GameSparksRT/Proto/LimitedPositionStream.cpp"
#	include "GameSparksRT/Proto/Packet.cpp"
#	include "GameSparksRT/Proto/PositionStream.cpp"
#	include "GameSparksRT/Proto/ReusableBinaryWriter.cpp"
#	include "GameSparksRT/Proto/RTData.Serializer.cpp"
#	include "GameSparksRT/Proto/RTVal.cpp"
#	include "GameSparksRT/RTData.cpp"
#	include "GameSparksRT/RTSessionImpl.cpp"
#	include "System/IO/BinaryReader.cpp"
#	include "System/IO/BinaryWriter.cpp"
#	include "System/IO/MemoryStream.cpp"
#	include "System/IO/Stream.cpp"
#	include "System/Net/Sockets/NetworkStream.cpp"
#	include "System/Net/Sockets/Socket.cpp"
#	include "System/Net/Sockets/TLSSocket.cpp"
#	include "System/Net/Sockets/TcpClient.cpp"
#	include "System/Net/Sockets/UdpClient.cpp"
#	include "System/Text/Encoding/UTF8.cpp"
#	include "System/Threading/Thread.cpp"
#endif

#undef PF_MAX

// so that unreal still includes MinWindows.h
#ifdef _WINDOWS_
#	undef _WINDOWS_
// Undo any Windows defines.
#	undef uint8
#	undef uint16
#	undef uint32
#	undef int32
#	undef float
#	undef MAX_uint8
#	undef MAX_uint16
#	undef MAX_uint32
#	undef MAX_int32
#	undef CDECL
#	undef PF_MAX
#	undef PlaySound
#	undef DrawText
#	undef CaptureStackBackTrace
#	undef MemoryBarrier
#	undef DeleteFile
#	undef MoveFile
#	undef CopyFile
#	undef CreateDirectory
#endif

#undef UI
