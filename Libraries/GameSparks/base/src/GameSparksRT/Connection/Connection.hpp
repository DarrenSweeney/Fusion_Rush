#ifndef _GAMESPARKSRT_CONNECTION_HPP_
#define _GAMESPARKSRT_CONNECTION_HPP_

#include <string>
#include <mutex>
#include "../IRTSessionInternal.hpp"
#include "../../System/Net/IPEndPoint.hpp"
#include "../../System/Failable.hpp"

namespace GameSparks { namespace RT { namespace Proto {
	class Packet;
}}}

namespace GameSparks { namespace RT { namespace Connection {

	class Connection
	{
		public:
			Connection (const std::string& remoteHost, const std::string& port, IRTSessionInternal* session);
			virtual System::Failable<int> Send(const Commands::RTRequest &request) =0;

			void Stop(){
				this->stopped = true;
				StopInternal ();
			}
			virtual void StopInternal () =0;
		protected:
			System::Failable<void> OnPacketReceived(Proto::Packet& p); // p is not const, because the ownership of p.Command is moved

			System::Net::IPEndPoint remoteEndPoint;
			IRTSessionInternal* session;
			std::recursive_mutex sessionMutex;
			volatile bool stopped;
		private:
	};

}}} /* namespace GameSparks.RT.Connection */

#endif /* _GAMESPARKSRT_CONNECTION_HPP_ */
