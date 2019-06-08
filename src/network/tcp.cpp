#include <network/tcp.hpp>
#include <exception/exception.hpp>

namespace tcp
{

Socket::Socket(const std::string& ip, const int port)
    : BaseSocket(SOCK_STREAM, ip.c_str(), port)
{
    ;
}

void Socket::send(DataProtocol &dataProtocol)
{
    auto [buf, len] = dataProtocol.serialize();
    if (::send(BaseSocket::getFd(), buf, len, 0) == 0)
        throw Exception("Can't send(): " + std::string(::strerror(errno)), errno);
}

void Socket::recv(DataProtocol &dataProtocol)
{
    size_t len = 0;
    void *buf = nullptr;

    if (::recv(BaseSocket::getFd(), buf, len, 0) != 0)
        throw Exception("Can't recv(): " + std::string(::strerror(errno)), errno);

    dataProtocol.deserialize();
}

void Socket::listen(int maxConnextions)
{
    if (::listen(BaseSocket::getFd(), maxConnextions) != 0)
        throw Exception("Can't listen(): " + std::string(::strerror(errno)), errno);
}

void Socket::connect()
{
    auto addr = BaseSocket::getAddr();
    if (::connect(BaseSocket::getFd(), (struct sockaddr* )&addr, sizeof(addr)) != 0)
        throw Exception("Can't connect(): " + std::string(::strerror(errno)), errno);
}

void Socket::accept()
{
    socklen_t addrLen;
    struct sockaddr clientAddr;

    auto clientFd = ::accept(BaseSocket::getFd(), &clientAddr, &addrLen);
    if (clientFd == -1)
        throw Exception("Can't accept(): " + std::string(::strerror(errno)), errno);
}

}