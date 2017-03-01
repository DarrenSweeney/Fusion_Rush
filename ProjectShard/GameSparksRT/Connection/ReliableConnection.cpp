#include "../../System/Exception.hpp"
#include <iostream>
#include "./ReliableConnection.hpp"
#include "../Commands/Requests/LoginCommand.hpp"
#include "../Proto/PositionStream.hpp"

namespace GameSparks { namespace RT { namespace Connection {

using namespace System::Net::Sockets;
using namespace System;
using namespace GameSparks::RT::Commands;
using namespace Com::Gamesparks::Realtime::Proto;

ReliableConnection::ReliableConnection  (const std::string& remotehost, const std::string& remoteport, IRTSessionInternal* session)
        :Connection(remotehost, remoteport, session)
        ,client(AddressFamily::InterNetwork)
{
    assert(session);
    //client = new TcpClient(AddressFamily.InterNetwork);
    client.NoDelay(true);
    client.BeginConnect ({remotehost, remoteport}, [this](const IAsyncResult& ar){
		client.Client().SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::KeepAlive, true);
		ConnectCallback(ar);
	});
}

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wshadow"
#endif

#if defined(_MSC_VER)
#	pragma warning (push)
#	pragma warning (disable:4456)
#endif

System::Failable<int> ReliableConnection::Send(const RTRequest& request){
    /*if (client.Connected()) {
        Packet p = request.ToPacket (*session, false);
        Packet::SerializeLengthDelimited (client.GetStream (), p);
    }*/
    if (client.Connected()) {
        Packet p = request.ToPacket (*session, false);
        GS_TRY
        {
            GS_ASSIGN_OR_CATCH(tmp, Packet::SerializeLengthDelimited (client.GetStream (), p));
            return tmp;
        }
        GS_CATCH(e)
        {
            std::clog << e << std::endl;
            if (session != nullptr && !stopped) {
                session->SetConnectState(GameSparksRT::ConnectState::Disconnected);
                session->Log ("ReliableConnection", GameSparksRT::LogLevel::LL_DEBUG, e.Format());

                // without exception support enabled in the compiler, we're not able to catch exceptions in client code
                GS_TRY
                {
                    session->OnReady (false);
                } GS_CATCH(e) {(void)e;}
            }
            return 0;
        }
    }
    return -1;
}

#if defined(_MSC_VER)
#	pragma warning (pop)
#endif

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif

void ReliableConnection::ConnectCallback(IAsyncResult /*result*/)
{
    //We can get here is the connection fails and the monitor thread
    // calls close. We should just do nothing at this point
    if (!client.Connected()) {
        return;
    }

    if (stopped) {
        if (client.Connected()) {
            client.Close ();
        }
        return;
    }

    //Each time a tcp connection is established we re-authenticate
    GS_TRY
    {
        LoginCommand loginCmd(session->ConnectToken());
        GS_CALL_OR_CATCH(Send (loginCmd));

        Packet p;
        {
            std::lock_guard<std::recursive_mutex> lock(sessionMutex);
            if(!session) return; // re-evaluate for expression
            p = Packet(*session);  // reset packet to default state
        }


        PositionStream rss(client.GetStream ());

        // read while all is good. if something goes wrong execute the GS_CATCH-block
        System::Failable<void> inner_result = {};
        System::Failable<bool> outer_result = {true};
        for(    outer_result = read(rss, p);
                inner_result.isOK() &&
                session &&
                outer_result.isOK() &&
                outer_result.GetResult();
                outer_result = read(rss, p)
        )
        {
            inner_result = OnPacketReceived(p);

            if (!inner_result.isOK())
            {
                continue; // re-evaluate for expression
            }

            {
                std::lock_guard<std::recursive_mutex> lock(sessionMutex);
                if(!session) continue; // re-evaluate for expression
                p = Packet(*session);  // reset packet to default state
            }
        }

        if(!outer_result.isOK())
            GS_PASS_EXCEPTION_TO_CATCH(outer_result.GetException());

        if(!inner_result.isOK())
            GS_PASS_EXCEPTION_TO_CATCH(inner_result.GetException());
    }
    GS_CATCH(e)
    {
        std::lock_guard<std::recursive_mutex> lock(sessionMutex);
        if (session != nullptr && !stopped) {
            session->SetConnectState(GameSparksRT::ConnectState::Disconnected);

            session->Log ("ReliableConnection", GameSparksRT::LogLevel::LL_DEBUG, e.Format());

            //session->Log ("ReliableConnection", GameSparksRT::LogLevel::DEBUG, e.StackTrace);
            session->OnReady (false);
        }
    }
}


System::Failable<bool> ReliableConnection::read(PositionStream& stream, Packet& p)
{
    if (stopped) {
        return false;
    }

    GS_CALL_OR_THROW(Packet::DeserializeLengthDelimited (stream, stream.BinaryReader, p));
    //p.Session = session;
    p.Reliable = p.Reliable.GetValueOrDefault(true);
    return true;
}

void ReliableConnection::StopInternal() {
    std::lock_guard<std::recursive_mutex> lock(sessionMutex);

    GS_TRY
    {
        if(client.Connected())
            client.Close ();
    }
    GS_CATCH(e){(void)e;}
    // Null the session, as we no longer want this connection to be able to mutate it
    session = nullptr;
}

void ReliableConnection::Poll() {
    client.Poll();
}

}}} /* namespace GameSparks.RT.Connection */
