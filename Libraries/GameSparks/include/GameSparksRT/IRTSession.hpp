#ifndef _GAMESPARKSRT_IRTSESSION_HPP_
#define _GAMESPARKSRT_IRTSESSION_HPP_

#include <GameSparksRT/Forwards.hpp>
#include <System/Nullable.hpp>
#include <System/ArraySegment.hpp>
#include <vector>
#include <System/Bytes.hpp>
#include "GameSparksRT.hpp"

namespace GameSparks { namespace RT {

	/*!
	 * Sessions are created via a GameSparksRTSessionBuilder. IRTSession objects are used to send data
	 * to the peers. Make sure to call Update() every frame. To listen for session related
	 * events inherit from IRTSessionListener.
	 */
	class IRTSession
	{
		public:
			/// <summary>
			/// Starts the session and connects to the real time services.
			/// </summary>
			virtual void Start () =0;

			/// <summary>
			/// Starts the session and disconnects from the real time services.
			/// </summary>
			virtual void Stop () =0;

			/// <summary>
			/// The peerId of the current player.
			/// </summary>
			System::Nullable<int> PeerId;

			/// <summary>
			/// Indicates if the SDK is Ready and connected
			/// </summary>
			bool Ready = false;

			/// <summary>
			/// The list of peers who are currently connected.
			/// </summary>
			std::vector<int> ActivePeers;

			/// <summary>
			/// The connection state of the session.
			/// </summary>
			virtual GameSparksRT::ConnectState GetConnectState() const = 0;

			/// <summary>
			/// Sends a message to other players
			/// </summary>
			/// <param name="opCode">The opCode to send</param>
			/// <param name="deliveryIntent">How this message should be sent.</param>
			/// <param name="payload">Th byte arry to send</param>
			/// <param name="targetPlayers">The list of players to send to (empty to send to all)</param>
			virtual int SendData(int opCode, GameSparksRT::DeliveryIntent intent, const System::Bytes &payload,
								 const RTData &data, const std::vector<int> &targetPlayers) = 0;

			/// <summary>
			/// Sends a strucured message to other players
			/// </summary>
			/// <param name="opCode">The opCode to send</param>
			/// <param name="deliveryIntent">How this message should be sent.</param>
			/// <param name="data">The RTData object to send</param>
			/// <param name="targetPlayers">The list of players to send to (empty to send to all)</param>
			virtual int SendRTData(int opCode, GameSparksRT::DeliveryIntent deliveryIntent, const RTData &data,
								   const std::vector<int> &targetPlayer) =0;

			/// <summary>
			/// Sends a byte[] to other players
			/// </summary>
			/// <param name="opCode">The opCode to send</param>
			/// <param name="deliveryIntent">How this message should be sent.</param>
			/// <param name="payload">bytes to send, as an ArraySegment<c> struct</c></param>
			/// <param name="targetPlayers">The list of players to send to (empty to send to all)</param>
			virtual int SendBytes(int opCode, GameSparksRT::DeliveryIntent deliveryIntent,
								  const System::ArraySegment<System::Byte> &payload,
								  const std::vector<int> &targetPlayer) =0;

			/// <summary>
			/// Sends both RTData and bytes to other players
			/// </summary>
			/// <param name="opCode">The opCode to send</param>
			/// <param name="deliveryIntent">How this message should be sent.</param>
			/// <param name="payload">bytes to send, as an ArraySegment<c> struct</c></param>
			/// <param name="targetPlayers">The list of players to send to (empty to send to all)</param>
			virtual int SendRTDataAndBytes(int opCode, GameSparksRT::DeliveryIntent intent,
										   const System::ArraySegment<System::Byte> &payload, const RTData &data,
										   const std::vector<int> &targetPlayer) =0;

			/// <summary>
			/// This method should be called as frequently as possible by the thread you want
			/// Your callbacks to execute on. In unity, you should call this from an Update
			/// method in a MonoBehaviour
			/// </summary>
			virtual void Update() = 0;


			virtual ~IRTSession(){}
		protected:
			friend class CustomCommand;
			friend class GameSparksRTSessionBuilder;
			friend class IRTSessionListener;

			/// <summary>
			/// The user supplied session listener.
			/// </summary>
			IRTSessionListener* SessionListener = nullptr;
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_IRTSESSION_HPP_ */
