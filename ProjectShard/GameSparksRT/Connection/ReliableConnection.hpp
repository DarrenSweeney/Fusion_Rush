#ifndef _GAMESPARKSRT_RELIABLECONNECTION_HPP_
#define _GAMESPARKSRT_RELIABLECONNECTION_HPP_

#include "./Connection.hpp"
#include "../../System/IAsyncResult.hpp"
#include "../../System/Net/Sockets/TcpClient.hpp"
#include "../Proto/Packet.hpp"

namespace GameSparks { namespace RT { namespace Connection {

	class ReliableConnection : public Connection
	{
		public:
			ReliableConnection  (const std::string& remotehost, const std::string& remoteport, IRTSessionInternal* session);
			virtual System::Failable<int> Send(const Commands::RTRequest& request) override;
			virtual void StopInternal() override;

			void Poll();
		private:
			void ConnectCallback(System::IAsyncResult result);
			System::Failable<bool> read(PositionStream& stream, Proto::Packet& p);

			System::Net::Sockets::TcpClient client;
	};

}}} /* namespace GameSparks.RT.Connection */

#endif /* _GAMESPARKSRT_RELIABLECONNECTION_HPP_ */
