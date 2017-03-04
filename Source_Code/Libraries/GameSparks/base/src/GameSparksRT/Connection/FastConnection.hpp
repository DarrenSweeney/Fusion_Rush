#ifndef _GAMESPARKSRT_FASTCONNECTION_HPP_
#define _GAMESPARKSRT_FASTCONNECTION_HPP_

#include "./Connection.hpp"
#include <GameSparksRT/Forwards.hpp>
#include "../../System/Net/Sockets/UdpClient.hpp"
#include "../Proto/ReusableBinaryWriter.hpp"
#include "../../System/AsyncCallback.hpp"

namespace System {class IAsyncResult;}

namespace GameSparks { namespace RT { namespace Connection {

	class FastConnection : public Connection
	{
		public:
			FastConnection (const std::string& remotehost, const std::string& port, IRTSessionInternal* session);
			virtual System::Failable<int> Send(const Commands::RTRequest &request) override;
			virtual void StopInternal() override;

			System::Bytes buffer = System::Bytes(GameSparksRT::MAX_MESSAGE_SIZE_BYTES);
		private:
			void DoLogin();
			void Recv(const System::IAsyncResult& res);
			void ReadBuffer(int read);
			System::Failable<void> SyncReceive();

			System::Net::Sockets::UdpClient client;
			int maxConnectAttempts = 20;
			int reconnectSleep = 200;

			System::AsyncCallback callback;
			BinaryWriteMemoryStream ms;
	};

}}} /* namespace GameSparks.RT.Connection */

#endif /* _GAMESPARKSRT_FASTCONNECTION_HPP_ */
