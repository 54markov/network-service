#include <network/udp.hpp>

namespace udp
{

Socket::Socket(const std::string& ip, const int port)
    : BaseSocket(SOCK_STREAM, port, ip.c_str())
{
    ;
}


void Socket::send(DataProtocol &dataProtocol)
{
    // TODO
}

void Socket::recv(DataProtocol &dataProtocol)
{
    // TODO
}

}