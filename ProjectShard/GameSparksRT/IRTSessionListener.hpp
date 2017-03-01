#ifndef _GAMESPARKSRT_IRTSESSIONLISTENER_HPP_
#define _GAMESPARKSRT_IRTSESSIONLISTENER_HPP_

#include <GameSparksRT/GSLinking.hpp>

namespace GameSparks { namespace RT {

	class RTPacket;
	class IRTSession;

	/*!
	 * Register an implementation of this interface via GameSparksRTSessionBuilder::SetListener() when building the session to listen
	 * for session related events.
	 */
	class GS_API IRTSessionListener
	{
		public:
			/// <summary>
			/// Executed when another player joins the room.
			/// </summary>
			/// <param name="peerId">The player who has just joined</param>
			virtual void OnPlayerConnect (int /*peerId*/) {};

			/// <summary>
			/// Executed when another player leaves the room.
			/// </summary>
			/// <param name="peerId">The player who has just left</param>
			virtual void OnPlayerDisconnect (int /*peerId*/) {};

			/// <summary>
			/// Executed when the SDK moves between a ready and non ready state
			/// </summary>
			/// <param name="ready">Whether the SDK is in a ready state (or not)</param>
			virtual void OnReady (bool /*ready*/) {};

			/// <summary>
			/// Executed when the SDK recieves a message from another player via SendPacket
			/// </summary>
			/// <param name="opCode">The opCode sent by the other player</param>
			/// <param name="sender">The peerId of the other player</param>
			/// <param name="stream">The stream of bytes sent by the other player</param>
			/// <param name="length">The number of bytes in the stream that can be read</param>
			virtual void OnPacket (const RTPacket& /*packet*/) {};

		protected:
			virtual ~IRTSessionListener();
		private:
			friend class GameSparksRTSessionBuilder;
			friend class RTSessionImpl;
			IRTSession* session = nullptr;
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_IRTSESSIONLISTENER_HPP_ */
