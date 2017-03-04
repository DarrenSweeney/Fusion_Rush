#ifndef _GAMESPARKSRT_RTDATA_HPP_
#define _GAMESPARKSRT_RTDATA_HPP_

#include <GameSparksRT/Forwards.hpp>
#include <GameSparksRT/GameSparksRT.hpp>
#include <GameSparksRT/Proto/RTVal.hpp>
#include <GameSparksRT/GSLinking.hpp>
#include <System/Nullable.hpp>
#include <System/Bytes.hpp>
#include <System/FailableForward.hpp>
#include <string>
#include <ostream>
#include <array>
#include "../../src/System/Failable.hpp"

namespace System{
	namespace IO
	{
		class Stream;
		class BinaryReader;
	}
}

namespace GameSparks { namespace RT {

    /*!
     * Can be used to represent points and directions in one to four dimensional space.
     */
    class RTVector
    {
        public:
            System::Nullable<float> x;
            System::Nullable<float> y;
            System::Nullable<float> z;
            System::Nullable<float> w;

            RTVector() {}
            RTVector(float x_) : x(x_) {}
            RTVector(float x_, float y_) : x(x_), y(y_) {}
            RTVector(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
            RTVector(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
			friend std::ostream& operator << (std::ostream& os, const RTVector& p);

			bool operator == (const RTVector& o) const
			{
				return x == o.x && y == o.y && z == o.z && w == o.w;
			}
    };

	typedef unsigned int uint;

    /*!
     * This is used to represent strucutred data to be send to the session peers via IRTSession::SendData().
     * Be aware, that RTData indices start at one - not at zero.
     */
    class GS_API RTData
    {
        public:
            System::Nullable<int> GetInt(uint index) const;
            System::Nullable<RTVector> GetRTVector(uint index) const;
            System::Nullable<int64_t> GetLong(uint index) const;
            System::Nullable<float> GetFloat(uint index) const;
            System::Nullable<double> GetDouble(uint index) const;
            System::Nullable<std::string> GetString(uint index) const;
            System::Nullable<RTData> GetData(uint index) const;

            RTData& SetInt(uint index, int value);
            RTData& SetLong(uint index, int64_t value);
            RTData& SetRTVector(uint index, RTVector value);
            RTData& SetFloat(uint index, float value);
            RTData& SetDouble(uint index, double value);
            RTData& SetString(uint index, const std::string& value);
            RTData& SetData(uint index, const RTData& value);
            friend GS_API std::ostream& operator << (std::ostream& os, const RTData& p);
        private:
            friend Proto::RTValSerializer;
            friend Proto::RTDataSerializer;

            // maybe we want to store that sparse (std::map) ?
            std::array<Proto::RTVal, GameSparksRT::MAX_RTDATA_SLOTS> data;

            friend Proto::Packet;
            static System::Failable<void> WriteRTData (System::IO::Stream& stream, const RTData& instance);
            static System::Failable<void> ReadRTData (System::IO::Stream& stream, System::IO::BinaryReader& br, RTData& instance);
    };

    /*!
     * When you data arrives, an instance of this class is passed to your IRTSessionListener::OnPacket() method.
     */
	class RTPacket
	{
		public:
			RTPacket(int opCode, int sender, const System::Bytes& payload, const RTData& data)
			:OpCode(opCode)
			,Sender(sender)
			,Data(data)
			,Payload(payload) {}

			int OpCode; ///< the same value that was passed to send when sending the packet. OpCodes must be greater than zero.
			int Sender; ///< Who send this packet.
			int StreamLength;
			const RTData& Data; ///< The RTData object that was send. might be empty if IRTSession::SendBytes() was used.
			const System::Bytes& Payload; ///< Use this if you want to use your own data-serialization format.

            /// ostream operator for debug output.
			friend std::ostream& operator << (std::ostream& os, const RTPacket& p)
			{
				os << "OpCode=" << p.OpCode << ",Sender=" << p.Sender /*<< ",streamExists=" << std::boolalpha << (p.Stream != nullptr) */<< ",StreamLength=" << p.StreamLength << ",Data=" << p.Data;// << (Data != nullptr ? Data.ToString() : "");
				return os;
			}
	};

}} /* namespace GameSparks.RT */

#endif /* _GAMESPARKSRT_RTDATA_HPP_ */
