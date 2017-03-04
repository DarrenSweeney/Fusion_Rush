#include <thread>
#include <iostream>
#include "../Commands/Requests/LoginCommand.hpp"
#include "../../System/Exception.hpp"
#include "./FastConnection.hpp"
#include "../../System/Threading/Thread.hpp"

namespace System {class IAsyncResult;}

namespace GameSparks { namespace RT { namespace Connection {

FastConnection::FastConnection(const std::string &remotehost, const std::string& port,
                               IRTSessionInternal *session)
    : Connection(remotehost, port, session)
{
    callback = [this](const System::IAsyncResult& ar){Recv(ar);};
    client.EnableBroadcast(false);
    client.ExclusiveAddressUse(false);
    client.MulticastLoopback(false);
    client.BeginConnect (remoteEndPoint, [this](const System::IAsyncResult& /*ar*/){
		{
			std::lock_guard<std::recursive_mutex> lock(sessionMutex);
			if (!this->session) return;
			this->session->Log("FastConnection", GameSparksRT::LogLevel::LL_DEBUG, "UDP Address=" + client.Client().LocalEndPoint);
		}
        DoLogin ();
        client.Client().BeginReceive (buffer, callback);
    });
    //client.Connect (remoteEndPoint);
    //session->Log("FastConnection", GameSparksRT::LogLevel::DEBUG, "UDP Address=" + client.Client().LocalEndPoint);
    //client.Client().BeginReceive (buffer, 0, GameSparksRT::MAX_MESSAGE_SIZE_BYTES, 0, callback);
    //client.Client().BeginReceive (buffer, callback);
    //DoLogin ();
}

System::Failable<int> FastConnection::Send(const Commands::RTRequest &request) {
    System::IO::MemoryStream ms_;

    GS_CALL_OR_THROW(ms_.Position(0));
    Proto::Packet p = request.ToPacket(*session, true);

    GS_TRY
    {
        GS_CALL_OR_CATCH(Proto::Packet::SerializeLengthDelimited(ms_, p));
    }
    GS_CATCH(e) {(void)e;}

    GS_CALL_OR_THROW(client.Send (ms_.GetBuffer(), ms_.Position()));

    return ms_.Position();
}

void FastConnection::StopInternal() {
    // TODO: check if we need to close
    //if(client != nullptr)
    //    client.Close ();
    std::lock_guard<std::recursive_mutex> lock(sessionMutex);
    session = nullptr;
}

void FastConnection::DoLogin() {
    //TODO: locking!

    //std::thread([this](){
    //    System::Threading::Thread::SetName("FastConnection::DoLogin() thread");

        int attempts = 0;

        GS_TRY
        {
			std::lock_guard<std::recursive_mutex> lock(sessionMutex);

			while (session != nullptr && ++attempts < maxConnectAttempts && session->GetConnectState() < GameSparksRT::ConnectState::ReliableAndFastSend)
            {
                Com::Gamesparks::Realtime::Proto::LoginCommand loginCmd(session->ConnectToken());
                GS_CALL_OR_CATCH(Send (loginCmd));
                std::this_thread::sleep_for(std::chrono::milliseconds(reconnectSleep));
            }

            if(session)
            {
                session->OnReady (true);
            }
        }
        GS_CATCH(e) {(void)e;}
    //}).detach();
}

void FastConnection::Recv(const System::IAsyncResult& res)
{
    GS_TRY
    {
        int read = client.Client().EndReceive(res);
        ReadBuffer(read);
        GS_CALL_OR_CATCH(SyncReceive ());
    }
    GS_CATCH(e)
    {
        std::lock_guard<std::recursive_mutex> lock(sessionMutex);
        if(session)
        {
            session->Log("FastConnection EndReceive", GameSparksRT::LogLevel::LL_INFO, e.Format());
        }
        else
        {
            std::clog << "FastConnection EndReceive:" << e.Format() << std::endl;
        }
    }
    //finally
    {
        if (!stopped && session != nullptr)
        client.Client().BeginReceive (buffer, callback);
    }
}

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wshadow"
#endif

#if defined(_MSC_VER)
#	pragma warning (push)
#	pragma warning (disable:4456)
#endif

void FastConnection::ReadBuffer(int read)
{
    GS_TRY
    {
		std::lock_guard<std::recursive_mutex> lg(sessionMutex);
		if (!session)
			return;
		
		GS_CALL_OR_CATCH(ms.Position(0));
        GS_CALL_OR_CATCH(ms.Write (buffer, 0, read));
        GS_CALL_OR_CATCH(ms.Position(0));

        while (ms.Position() < read) {
            GS_TRY
            {
                assert(session);
                Commands::Packet p(*session);
                GS_CALL_OR_CATCH(Commands::Packet::DeserializeLengthDelimited (ms, ms.BinaryReader, p));
                p.Reliable = p.Reliable.GetValueOrDefault (false);
                GS_CALL_OR_CATCH(OnPacketReceived (p));
                p = Commands::Packet(*session); // reset packet to default state
            }
            GS_CATCH(e)
            {
                std::clog << e << std::endl;
                GS_PROGRAMMING_ERROR("decide what to do here!");
                assert(false);
            }
        }
    }
    GS_CATCH(e)
    {
        session->Log ("FastConnection read", GameSparksRT::LogLevel::LL_WARN, e.Format());
    }
}

#if defined(_MSC_VER)
#	pragma warning (pop)
#endif

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif /* __clang__ */

System::Failable<void> FastConnection::SyncReceive() {
    while (!stopped && session != nullptr) {
        GS_ASSIGN_OR_THROW(read, client.Client().Receive (buffer));
        if (read > 0) {
            ReadBuffer (read);
        }
    }
    return {};
}

}}} /* namespace GameSparks.RT.Connection */
