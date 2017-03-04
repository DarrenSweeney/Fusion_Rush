
#include "./ReusableBinaryWriter.hpp"

namespace GameSparks { namespace RT {

        BinaryWriteMemoryStream::BinaryWriteMemoryStream()
        :BinaryReader(*this)
        ,BinaryWriter(*this)
        {}

}} /* namespace GameSparks.RT */

	