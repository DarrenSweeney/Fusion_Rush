#ifndef _GAMESPARKSRT_POSITIONSTREAM_HPP_
#define _GAMESPARKSRT_POSITIONSTREAM_HPP_

#include "../../System/IO/Stream.hpp"
#include "../../System/IO/BinaryReader.hpp"
#include <vector>
#include <System/Bytes.hpp>

namespace GameSparks { namespace RT {

	class PositionStream : public System::IO::Stream
	{
		public:
			PositionStream(System::IO::Stream& baseStream)
			:BytesRead(0)
			, BinaryReader(*this)
			, stream(baseStream)
			{}

			int BytesRead = 0;

			System::IO::BinaryReader BinaryReader;

			//virtual void WriteByte(unsigned char Value) override;

			virtual System::Failable<int> Read(System::Bytes& buffer, int offset, int count) override;
			virtual System::Failable<int> ReadByte() override;

			virtual int Position() const override;

			virtual bool CanRead() const override;

	private:
			System::IO::Stream& stream;
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_POSITIONSTREAM_HPP_ */
