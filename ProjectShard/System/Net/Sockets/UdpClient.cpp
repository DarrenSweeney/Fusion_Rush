#include "./UdpClient.hpp"
//#include <mbedtls/net.h>

namespace System { namespace Net { namespace Sockets {

UdpClient::UdpClient()
:client(AddressFamily::InterNetwork, SocketType::Dgram, ProtocolType::Udp)
{

}

void UdpClient::BeginConnect(
    const IPEndPoint& endpoint,
    const AsyncCallback& requestCallback
)
{
    return client.BeginConnect(endpoint, requestCallback);
}

/*void UdpClient::Connect(const IPEndPoint &endpoint) {
    client.Connect(endpoint);
}*/

void UdpClient::EnableBroadcast(bool /*value*/) {
    //TODO: check if not needed
}

void UdpClient::ExclusiveAddressUse(bool /*value*/) {
    //TODO: check if not needed
}

void UdpClient::MulticastLoopback(bool /*value*/) {
    //TODO: check if not needed
}

Socket &UdpClient::Client() {
    return client;
}

Failable<void> UdpClient::Send(const Bytes &dgram, int bytes) {
    return client.Send(dgram, 0, bytes);
}

}}} /* namespace System.Net.Sockets */
