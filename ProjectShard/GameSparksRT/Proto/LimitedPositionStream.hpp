#ifndef _GAMESPARKSRT_LIMITEDPOSITIONSTREAM_HPP_
#define _GAMESPARKSRT_LIMITEDPOSITIONSTREAM_HPP_

#include <System/Bytes.hpp>
#include "./PositionStream.hpp"
#include <cstddef>
#include <assert.h>
#include <vector>

namespace GameSparks { namespace RT { namespace Proto {

	class LimitedPositionStream : public ::GameSparks::RT::PositionStream
	{
		public:
			LimitedPositionStream(System::IO::Stream& stream, size_t limit);

			System::Failable<int> Read(System::Bytes& buffer, int offset, int count) override
			{
				int toRead = (count > limit - BytesRead) ? (int)(limit - BytesRead) : count;
				return PositionStream::Read(buffer, offset, toRead);
			}

			System::Failable<int> ReadByte() override
			{
				return (BytesRead >= limit) ? -1 : PositionStream::ReadByte ();
			}

			void SkipToEnd()
			{
				if (BytesRead < limit) {
					System::Bytes discardBytes(256);
					auto r = Read (discardBytes, 0, 256);
					while (r.isOK() && 256 == r.GetResult()) {}
				}
			}

			virtual System::Failable<void> WriteByte(unsigned char /*value*/) override
			{
				assert(false);
				GS_THROW(System::NotImplementedException("LimitedPositionStream::WriteByte not implemented."));
				//return {};
			}


			virtual System::Failable<int64_t> Seek(int64_t offset, System::IO::SeekOrigin origin) override;

		private:
			int limit;
	};

}}} /* namespace GameSparks.RT.Proto */

#endif /* _GAMESPARKSRT_LIMITEDPOSITIONSTREAM_HPP_ */
