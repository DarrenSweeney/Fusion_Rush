#ifndef _GAMESPARKSRT_STREAM_HPP_
#define _GAMESPARKSRT_STREAM_HPP_

#include "SeekOrigin.hpp"
#include <cassert>
#include <System/Bytes.hpp>
#include "../NotImplementedException.hpp"
#include "../Failable.hpp"


namespace System { namespace IO {

	class Stream
	{
		public:
			virtual Failable<void> WriteByte(unsigned char value);// { assert(false); throw System::NotImplementedException("NotImplementedException"); }
			virtual Failable<void> Write(const System::Bytes& /*buffer*/, int /*offset*/, int /*size*/) { GS_PROGRAMMING_ERROR("not implemented"); GS_THROW(System::NotImplementedException("NotImplementedException")); }

			virtual Failable<int> ReadByte();// { assert(false); throw System::NotImplementedException("NotImplementedException"); }
			virtual Failable<int> Read(System::Bytes& /*buffer*/, int /*offset*/, int /*count*/) { GS_PROGRAMMING_ERROR("not implemented"); GS_THROW(System::NotImplementedException("NotImplementedException")); }

			virtual Failable<int64_t> Seek(int64_t /*offset*/, IO::SeekOrigin /*origin*/) { GS_PROGRAMMING_ERROR("not implemented"); GS_THROW(System::NotImplementedException("NotImplementedException")); }

			//virtual Failable<size_t> Position() const { GS_PROGRAMMING_ERROR("not implemented"); GS_THROW(System::NotImplementedException("NotImplementedException")); }
			virtual int Position() const { GS_PROGRAMMING_ERROR("not implemented"); return 0;/*GS_THROW(System::NotImplementedException("NotImplementedException"));*/ }
			virtual Failable<void> Position(
					const int /*pos*/) { GS_PROGRAMMING_ERROR("not implemented"); GS_THROW(System::NotImplementedException("NotImplementedException")); }

			virtual bool CanRead () const { assert(false); return false; }
			virtual bool CanWrite() const { assert(false); return false; }

			virtual ~Stream() {}
		private:
	};

}} /* namespace System */

#endif /* _GAMESPARKSRT_STREAM_HPP_ */
