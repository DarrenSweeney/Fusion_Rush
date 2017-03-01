#ifndef _GAMESPARKSRT_RTDATA_SERIALIZER_HPP_
#define _GAMESPARKSRT_RTDATA_SERIALIZER_HPP_

#include <GameSparksRT/Forwards.hpp>
#include "../../System/Failable.hpp"

namespace GameSparks { namespace RT { namespace Proto {

	class RTValSerializer
	{
		public:
			static System::Failable<void> ReadRTVal (System::IO::Stream& stream, System::IO::BinaryReader& br, RTVal& instance);
			static System::Failable<void> WriteRTVal (System::IO::Stream& stream, const RTVal& instance);
		private:
	};

	class RTDataSerializer
	{
		public:
			static System::Failable<void> ReadRTData (System::IO::Stream& stream, System::IO::BinaryReader& br, RTData& instance);
			static System::Failable<void> WriteRTData (System::IO::Stream& stream, const RTData& instance);
		private:
	};

}}} /* namespace GameSparks.RT.Proto */

#endif /* _GAMESPARKSRT_RTDATA_SERIALIZER_HPP_ */
