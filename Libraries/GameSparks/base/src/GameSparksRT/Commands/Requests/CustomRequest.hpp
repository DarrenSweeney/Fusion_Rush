#ifndef _GAMESPARKSRT_CUSTOMREQUEST_HPP_
#define _GAMESPARKSRT_CUSTOMREQUEST_HPP_

#include <System/Bytes.hpp>
#include "./RTRequest.hpp"
#include "../../../System/IO/Stream.hpp"

namespace GameSparks { namespace RT {

	class CustomRequest : public Commands::RTRequest
	{
		public:
			System::Bytes payload;

			CustomRequest(int opCode, GameSparksRT::DeliveryIntent intent, const System::ArraySegment<System::Byte>& payload, const RTData& data,  std::vector<int> targetPlayers);

			virtual System::Failable<void> Serialize(System::IO::Stream &stream) const override;
		private:
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_CUSTOMREQUEST_HPP_ */
