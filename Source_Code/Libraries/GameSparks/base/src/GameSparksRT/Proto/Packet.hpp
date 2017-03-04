#ifndef _GAMESPARKSRT_PACKET_HPP_
#define _GAMESPARKSRT_PACKET_HPP_

#include <list>
#include <vector>
#include <memory>

#include <System/Nullable.hpp>
#include <System/Bytes.hpp>

#include <GameSparksRT/Forwards.hpp>
#include <GameSparksRT/RTData.hpp>

#include "../../System/Failable.hpp"

namespace System
{
	namespace IO
	{
		class Stream;
		class BinaryReader;
	}
}

namespace GameSparks { namespace RT { namespace Proto {

	class Packet
	{
		public:
			Packet() : Session(nullptr) {}
			Packet(IRTSessionInternal& Session_) : Session(&Session_) {}

			int OpCode = std::numeric_limits<int>::lowest();
			System::Nullable<int> SequenceNumber;
			System::Nullable<int> RequestId;
			std::list<int> TargetPlayers;
			System::Nullable<int> Sender;
			System::Nullable<bool> Reliable;
			RTData Data;
			System::Bytes Payload;

			// extensions
			IRTSessionInternal* Session;// = nullptr;
			const GameSparks::RT::Commands::RTRequest* Request = nullptr;
			std::unique_ptr<IRTCommand> Command;
			bool hasPayload = false;
			System::Failable<void> WritePayload (System::IO::Stream& stream) const;

			//serializer
			static System::Failable<void> DeserializeLengthDelimited(System::IO::Stream& stream, System::IO::BinaryReader& br, Packet& instance);
			static System::Failable<void> Serialize(System::IO::Stream& stream, const Packet& instance);
			static System::Failable<int> SerializeLengthDelimited(System::IO::Stream &stream, const Packet &instance);

			#if defined(_MSC_VER) && _MSC_VER <= 1900
			// visual studio 2013 does not support generate default move constructors and assignemnt operators
			// http://stackoverflow.com/questions/26581262/default-move-constructor-in-visual-studio-2013-update-3
			Packet(Packet&& o)
			:OpCode(std::move(o.OpCode))
			,SequenceNumber(std::move(o.SequenceNumber))
			,RequestId(std::move(o.RequestId))
			,TargetPlayers(std::move(o.TargetPlayers))
			,Sender(std::move(o.Sender))
			,Reliable(std::move(o.Reliable))
			,Data(std::move(o.Data))
			,Payload(std::move(o.Payload))
			,Session(std::move(o.Session))
			,Request(std::move(o.Request))
			,Command(std::move(o.Command))
			,hasPayload(std::move(o.hasPayload))
			{}

			Packet& operator =(Packet&& o)
			{
				OpCode = std::move(o.OpCode);
				SequenceNumber = std::move(o.SequenceNumber);
				RequestId = std::move(o.RequestId);
				TargetPlayers = std::move(o.TargetPlayers);
				Sender = std::move(o.Sender);
				Reliable = std::move(o.Reliable);
				Data = std::move(o.Data);
				Payload = std::move(o.Payload);
				Session = std::move(o.Session);
				Request = std::move(o.Request);
				Command = std::move(o.Command);
				hasPayload = std::move(o.hasPayload);
				return *this;
			}
			#endif
		private:
			// extensions
			System::Failable<System::Bytes> ReadPayload (System::IO::Stream& stream);

			#if defined(_MSC_VER) && _MSC_VER <= 1900
			Packet(const Packet&);
			Packet& operator =(const Packet&);
			#endif
	};

}}} /* namespace GameSparks.RT.Proto */

#endif /* _GAMESPARKSRT_PACKET_HPP_ */
