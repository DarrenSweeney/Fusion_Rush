#ifndef _GAMESPARKSRT_REUSABLEBINARYWRITER_HPP_
#define _GAMESPARKSRT_REUSABLEBINARYWRITER_HPP_

#include "../../System/IO/MemoryStream.hpp"
#include "../../System/IO/BinaryReader.hpp"
#include "../../System/IO/BinaryWriter.hpp"

namespace GameSparks { namespace RT {

	class BinaryWriteMemoryStream : public System::IO::MemoryStream
	{
		public:
			BinaryWriteMemoryStream();

			System::IO::BinaryReader BinaryReader;
			System::IO::BinaryWriter BinaryWriter;
		private:
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_REUSABLEBINARYWRITER_HPP_ */
