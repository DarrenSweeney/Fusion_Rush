#ifndef _GAMESPARKSRT_RTREQUEST_HPP_
#define _GAMESPARKSRT_RTREQUEST_HPP_

#include "../../IRTSessionInternal.hpp"
#include "../../IRTCommand.hpp"
#include "../../Proto/Packet.hpp"
#include <GameSparksRT/GameSparksRT.hpp>

namespace GameSparks { namespace RT { namespace Commands {

	using GameSparks::RT::Proto::Packet;

	class RTRequest
	{
		public:
			RTRequest(int opCode) : OpCode(opCode) {}

			virtual Packet ToPacket(IRTSessionInternal& session, bool fast) const
			{
				Packet p(session);// = PooledObjects.PacketPool.Pop();
				p.OpCode = OpCode;
				p.Data = Data;

				if (!fast && intent != GameSparksRT::DeliveryIntent::RELIABLE) {
					p.Reliable = false;
				}

				p.Reliable = (intent == GameSparksRT::DeliveryIntent::RELIABLE);
				if (intent == GameSparksRT::DeliveryIntent::UNRELIABLE_SEQUENCED) {
					p.SequenceNumber = session.NextSequenceNumber ();
				}
				if (TargetPlayers.size() > 0) {
					p.TargetPlayers = TargetPlayers;
				}
				p.Request = this;
				return p;
			}

			virtual System::Failable<void> Serialize (System::IO::Stream& stream) const =0;

		protected:
			RTData Data;
			int OpCode;
			std::list<int> TargetPlayers;
			GameSparksRT::DeliveryIntent intent;

		private:
	};

}}} /* namespace GameSparks.RT.Commands */

#endif /* _GAMESPARKSRT_RTREQUEST_HPP_ */
