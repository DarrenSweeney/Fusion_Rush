
#include "./LimitedPositionStream.hpp"

namespace GameSparks { namespace RT { namespace Proto {

LimitedPositionStream::LimitedPositionStream(System::IO::Stream& stream_, size_t limit_)
:PositionStream(stream_)
,limit(int(limit_))
{

}

System::Failable<int64_t> LimitedPositionStream::Seek(int64_t /*offset*/, System::IO::SeekOrigin /*origin*/) {
    GS_PROGRAMMING_ERROR("Not Implemented");
    GS_THROW(System::NotImplementedException("LimitedPositionStream::Seek not implemented"))
    //return 0;
}

}}} /* namespace GameSparks.RT.Proto */
