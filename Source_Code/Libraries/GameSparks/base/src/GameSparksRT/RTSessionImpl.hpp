#ifndef _GAMESPARKSRT_RTSESSIONIMPL_HPP_
#define _GAMESPARKSRT_RTSESSIONIMPL_HPP_

#include <map>
#include <queue>
#include <thread>
#include <mutex>

#include <GameSparksRT/Forwards.hpp>
#include "./IRTSessionInternal.hpp"
#include "./IRTCommand.hpp"

namespace GameSparks { namespace RT {

	class RTSessionImpl : public IRTSessionInternal
	{
		public:
			RTSessionImpl (const std::string& connectToken, const std::string& hostName, const std::string& tcpPort, const std::string& udpPort);
			 virtual ~RTSessionImpl();

			virtual int SendData(int opCode, GameSparksRT::DeliveryIntent intent, const System::Bytes &payload,
								 const RTData &data, const std::vector<int> &targetPlayers) override;

            virtual int SendRTData(int opCode, GameSparksRT::DeliveryIntent deliveryIntent, const RTData &data,
								   const std::vector<int> &targetPlayers) override;

            virtual int SendBytes(int opCode, GameSparksRT::DeliveryIntent deliveryIntent,
								  const System::ArraySegment<System::Byte> &payload,
								  const std::vector<int> &targetPlayers) override;

            virtual int SendRTDataAndBytes(int opCode, GameSparksRT::DeliveryIntent intent,
										   const System::ArraySegment<System::Byte> &payload, const RTData &data,
										   const std::vector<int> &targetPlayers) override;

    		virtual void Stop() override;
			virtual void Start() override;
			virtual void Update() override;
			virtual std::string ConnectToken() const override;
			virtual void ConnectToken(const std::string& token) override;
			virtual std::string FastPort() const override;
			virtual void FastPort(const std::string&) override;

			virtual void ConnectReliable() override;
			virtual void ConnectFast() override;
			virtual bool ShouldExecute(int peerId, System::Nullable<int> sequence) override;
			virtual void SubmitAction(std::unique_ptr<IRTCommand>& action) override;
			virtual int NextSequenceNumber() override;
			virtual void OnPlayerConnect(int peerId) override;
			virtual void OnPlayerDisconnect(int peerId) override;
			virtual void OnReady(bool ready) override;
			virtual void OnPacket(const RTPacket &packet) override;


			virtual GameSparksRT::ConnectState GetConnectState() const override;
			virtual void SetConnectState(GameSparksRT::ConnectState value) override;

	private:
			virtual void DoLog(const std::string &tag, GameSparks::RT::GameSparksRT::LogLevel level, const std::string &msg) override;
			void ResetSequenceForPeer (int peerId);
			void CheckConnection();
			std::unique_ptr<IRTCommand> GetNextAction();

			// note: it's important, that those two are the first members so that they are created first and destroyed last.
			std::queue<std::unique_ptr<IRTCommand>> actionQueue;
			std::mutex actionQueueMutex;

			std::unique_ptr<Connection::ReliableConnection> reliableConnection;
			std::unique_ptr<Connection::FastConnection> fastConnection;

			bool running = false;
			std::chrono::steady_clock::time_point mustConnnectBy;

			std::string connectToken;
			std::string hostName;
			std::string TcpPort;
			std::string fastPort;
			std::map<int, int> peerMaxSequenceNumbers;

			int sequenceNumber = 0;

			GameSparksRT::ConnectState internalState = GameSparksRT::ConnectState::Disconnected;

			std::mutex sendMutex;
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_RTSESSIONIMPL_HPP_ */
