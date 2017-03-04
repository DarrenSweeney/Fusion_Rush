#include <assert.h>
#include <vector>
#include "./NetworkStream.hpp"

namespace System { namespace Net { namespace Sockets {

NetworkStream::NetworkStream(Socket& socket_)
:socket(socket_)
{

}

Failable<void> NetworkStream::Write(const System::Bytes &buffer, int offset, int size) {
    return socket.Send(buffer, offset, size);
}

bool NetworkStream::CanRead() const {
    return socket.Connected();
}

bool NetworkStream::CanWrite() const {
    return socket.Connected();
}

Failable<int> NetworkStream::Read(System::Bytes &buffer, int offset, int count) {
    return socket.Receive(buffer,offset,count);
}

}}}
