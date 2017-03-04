#ifndef _GAMESPARKSRT_PROTOCOLBUFFEREXCEPTION_HPP_
#define _GAMESPARKSRT_PROTOCOLBUFFEREXCEPTION_HPP_

#include "../../System/Exception.hpp"

namespace GameSparks { namespace RT { namespace Proto {

	class ProtocolBufferException : public System::Exception
	{
		public: ProtocolBufferException(const std::string what) : Exception(what, "ProtocolBufferException") {}
	};

}}} /* namespace GameSparks.RT.Proto */

#endif /* _GAMESPARKSRT_PROTOCOLBUFFEREXCEPTION_HPP_ */
