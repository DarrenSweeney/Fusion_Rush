#ifndef _GAMESPARKSRT_PACKET_EXT_HPP_
#define _GAMESPARKSRT_PACKET_EXT_HPP_

#include <GameSparksRT/Forwards.hpp>
#include <System/Nullable.hpp>
#include <System/FailableForward.hpp>
#include <GameSparksRT/GSLinking.hpp>
#include <string>

namespace GameSparks { namespace RT {

	/// protocol related classes
	namespace Proto {

	/// Type erasure datatype used by RTData
	class GS_API RTVal
	{
		public:
			RTVal();
			RTVal(int64_t value);
			RTVal(float value);
			RTVal(double value);
			RTVal(const std::string& value);
			RTVal(const RTData& value);
			explicit RTVal(const RTVector& value);

            /// return true, if any of the values is set
            explicit operator bool() const;

            friend std::ostream& operator << (std::ostream& os, const RTVal&);
		private:
            friend class RTValSerializer;
            friend class RTDataSerializer;
            friend RTData;

			static System::Failable<void> DeserializeLengthDelimited(System::IO::Stream& stream, System::IO::BinaryReader& br, RTVal& instance);
			System::Failable<void> SerializeLengthDelimited(System::IO::Stream& stream);

			//TODO: compacter storage, by using type enum and union (or something like boost::variant)
			System::Nullable<int64_t> long_val;
			System::Nullable<float> float_val;
			System::Nullable<double> double_val;
			System::Nullable<RTData> data_val;
			System::Nullable<std::string> string_val;
			System::Nullable<RTVector> vec_val;
	};

}}} /* namespace GameSparks.RT.Proto */

#endif /* _GAMESPARKSRT_PACKET_EXT_HPP_ */
