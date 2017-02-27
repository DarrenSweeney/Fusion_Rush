#ifndef _GAMESPARKSRT_GAMESPARKSRT_HPP_
#define _GAMESPARKSRT_GAMESPARKSRT_HPP_

#include <GameSparksRT/Forwards.hpp>
#include <GameSparksRT/GSLinking.hpp>
#include <string>
#include <functional>
#include <map>

// unfortunaltely, WinSpool.h defines SetPort
#if defined(SetPort)
#	undef SetPort
#endif

namespace GameSparks {

	/*!
	 * GameSparks SDK Realtime capabilities
	 */
	namespace RT {

	/*!
	 * Use this to build an RTSession with tokens obtained via an GameSparks::Api::Requests::MatchmakingRequest.
	 * \include sample07Realtime.cpp
	 */
	class GS_API GameSparksRTSessionBuilder
	{
		public:
			/// Constructor
			GameSparksRTSessionBuilder();

			/// Destructor
			~GameSparksRTSessionBuilder();

			/// sets the connect token to use for the session. obtained via  MatchmakingRequest::GetAccessToken().GetValue().
			GameSparksRTSessionBuilder& SetConnectToken(const std::string& connectToken);

			/// sets the host to use for the session. obtained via  MatchmakingRequest::GetHost().GetValue().
			GameSparksRTSessionBuilder& SetHost(const std::string& host);

			/// sets the port to use for the session. obtained via  MatchmakingRequest::GetPort().GetValue().
			GameSparksRTSessionBuilder& SetPort(const std::string& port);

			/// sets the port to use for the session. obtained via  MatchmakingRequest::GetPort().GetValue().
			GameSparksRTSessionBuilder& SetPort(int port);

			/// sets the session listener to listen for session related events.
			GameSparksRTSessionBuilder& SetListener(IRTSessionListener* listener);

			/// Build the IRTSession. caller owns the return value. make sure to put it into a std::unique_ptr or std::shared_ptr (or delete it manually).
			IRTSession* Build() const;
		private:
			// we're using the pimpl idom for the member variables to avoid dll linkage issues
			struct Pimpl
			{
				std::string connectToken;
				std::string host;
				std::string port;
				IRTSessionListener* listener = nullptr;
			};
			Pimpl* pimpl;
	};

	// instantiation as GS_API to avoid DLL linking issues
	#if PLATFORM_WINDOWS && defined(GS_BUILDING_DLL)
	template class GS_API std::function<void(const std::string&)>;
	#endif

	/*!
	 * Uses for settings related to the RT SDK.
	 */
	class GS_API GameSparksRT
	{
		public:
			enum {
				MAX_RTDATA_SLOTS = 128,
				MAX_MESSAGE_SIZE_BYTES = 1024
			};

			static GameSparksRTSessionBuilder SessionBuilder();

			/// <summary>
			/// Log level.
			/// </summary>
			enum class LogLevel {
				/// <summary>
				/// Log at DEBUG
				/// </summary>
				LL_DEBUG=0,
				/// <summary>
				/// Log at INFO
				/// </summary>
				LL_INFO=1,
				/// <summary>
				/// Log at WARN
				/// </summary>
				LL_WARN=2,
				/// <summary>
				/// Log at ERROR
				/// </summary>
				LL_ERROR=3
			};

			/// <summary>
			/// The state of the current SDK
			/// </summary>
			enum class ConnectState
			{
				/// <summary>
				/// Disconnected.
				/// </summary>
				Disconnected = 0,

				/// <summary>
				/// Connecting.
				/// </summary>
				Connecting = 1,

				/// <summary>
				/// Only a TCP connection is established.
				/// </summary>
				ReliableOnly = 2,

				/// <summary>
				/// We've successfully send some UDP and the server has recieved it, but have not recieved any
				/// </summary>
				ReliableAndFastSend = 3,

				/// <summary>
				/// All systems go. We can send and recieve UCP.
				/// </summary>
				ReliableAndFast = 4
			};

			/// <summary>
			/// How the message should be attempted to be sent.
			/// If ConnectState==ReliableOnly the message will be sent as RELIABLE
			/// </summary>
			enum class DeliveryIntent
			{
				/// <summary>
				/// Send over TCP
				/// </summary>
				RELIABLE = 0,

				/// <summary>
				/// Send over UDP, don't discard out of sequence packets
				/// </summary>
				UNRELIABLE = 1,

				/// <summary>
				/// Send over UDP, discard out of sequence packets
				/// </summary>
				UNRELIABLE_SEQUENCED = 2
			};

			static void SetRootLogLevel(LogLevel level);
			static void SetLogLevel(const std::string& tag, LogLevel level);
			static std::function<void (const std::string&)> Logger;
			static bool ShouldLog(const std::string& tag, LogLevel level);

			// default to five seconds
			static int TCP_CONNECT_TIMEOUT_SECONDS;
		private:
			static GameSparksRT::LogLevel logLevel;
	};

	/// \example sample07Realtime.cpp This is a basic example of using the RT SDK.


}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_GAMESPARKSRT_HPP_ */
