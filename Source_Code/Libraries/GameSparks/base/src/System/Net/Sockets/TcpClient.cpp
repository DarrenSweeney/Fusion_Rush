#include "./TcpClient.hpp"
#include <cassert>

#include "SocketOptionLevel.hpp"

namespace System { namespace Net { namespace Sockets {

TcpClient::TcpClient(AddressFamily addressFamily)
:client(addressFamily)//, SocketType::Stream, ProtocolType::Tcp)
,networkStream(client)
{

}


void TcpClient::NoDelay(bool value)
{
    client.NoDelay(value);
}


bool TcpClient::NoDelay() const
{
    return client.NoDelay();
}

bool TcpClient::Connected() const
{
    return client.Connected();
}

Socket& TcpClient::Client()
{
    return client;
}

void TcpClient::Close()
{

}

NetworkStream& TcpClient::GetStream()
{
    return networkStream;
}

void TcpClient::BeginConnect(
        const IPEndPoint& endpoint,
        const AsyncCallback& requestCallback
)
{
    return client.BeginConnect(endpoint, requestCallback);
}


void TcpClient::Poll() {
    client.Poll();
}

}}}
