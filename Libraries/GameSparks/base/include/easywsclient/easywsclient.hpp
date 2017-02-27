#ifndef EASYWSCLIENT_HPP_20120819_MIOFVASDTNUASZDQPLFD
#define EASYWSCLIENT_HPP_20120819_MIOFVASDTNUASZDQPLFD

// This code comes from:
// https://github.com/dhbaird/easywsclient
//
// To get the latest version:
// wget https://raw.github.com/dhbaird/easywsclient/master/easywsclient.hpp
// wget https://raw.github.com/dhbaird/easywsclient/master/easywsclient.cpp

#include <GameSparks/gsstl.h>

namespace easywsclient {
	/* Used to pass Errors to the error callback */
	struct WSError
	{
		enum Code
		{
			UNEXPECTED_MESSAGE, ///< The server sent an unexpected message
			DNS_LOOKUP_FAILED,  ///< gethostbyname failed to lookup the host
			RECV_FAILED, ///< recv or SSL_read returned a nagative value
			CONNECTION_CLOSED, ///< the connection was closed - i.e. recv or SSL_read returned zero. Not necessarily an error
			SEND_FAILED, ///< send or SSL_write returned a nagative value
			SOCKET_CREATION_FAILED, ///< The socket constructor returned INVALID_SOCKET
			CONNECT_FAILED, ///< The call to connect() returned SOCKET_ERROR
			SSL_CTX_NEW_FAILED, ///< SSL_CTX_new returned null
			SSL_NEW_FAILED, ///< SSL_new returned null
			SSL_SET_FD_FAILED, ///< SSL_set_fd returned 0
			SSL_CONNECT_FAILED, ///< SSL_connect returned a value not equal to 1
			CLOSED_DURING_WS_HANDSHAKE, ///< recv or SSL_read returned 0 during the websocket handshake
			INVALID_STATUS_LINE_DURING_WS_HANDSHAKE, ///< the status line received from the server during the websocket handshake was to long to fit into the buffer
			BAD_STATUS_CODE ///< the HTTP status code returned was not 101 (Switching Protocols)
		};

		WSError(Code code_, const gsstl::string& message_) : code(code_), message(message_){}

		const Code code; ///< one of the error codes
		const gsstl::string message; ///< a more or less human readable error description

		private:
			const WSError& operator=( const WSError& );
	};

	class WebSocket
	{
		public:
		typedef void (*WSMessageCallback)(const gsstl::string &, void*);
		typedef void(*WSErrorCallback)(const WSError&, void*);
		typedef WebSocket * pointer;
		typedef enum readyStateValues { CLOSING, CLOSED, CONNECTING, OPEN } readyStateValues;

		// Factories:
		static pointer create_dummy();
		static pointer from_url(const gsstl::string& url, const gsstl::string& origin = gsstl::string());
		static pointer from_url_no_mask(const gsstl::string& url, const gsstl::string& origin = gsstl::string());

		// Interfaces:
		virtual ~WebSocket() { }
		virtual void poll(int timeout, WSErrorCallback errorCallback, void* userData) = 0; // timeout in milliseconds
		virtual void send(const gsstl::string& message) = 0;
		virtual void sendPing() = 0;
		virtual void close() = 0;
		virtual readyStateValues getReadyState() const = 0;

		void dispatch(WSMessageCallback messageCallback, WSErrorCallback errorCallback, void* userData) {
			_dispatch(messageCallback, errorCallback, userData);
		}
        
	protected:
		//struct Callback { virtual void operator()(const gsstl::string& message) = 0; };
		virtual void _dispatch(WSMessageCallback message_callback, WSErrorCallback error_callback, void* data) = 0;
        
    protected:
        enum dnsLookup
        {
            keNone,
            keInprogress,
            keComplete,
            keFailed
        };
        
        volatile dnsLookup ipLookup;
        
        gsstl::string m_host;
        gsstl::string m_path;
        gsstl::string m_url;
        gsstl::string m_origin;
        
        int m_port;
    };

} // namespace easywsclient

#endif /* EASYWSCLIENT_HPP_20120819_MIOFVASDTNUASZDQPLFD */
