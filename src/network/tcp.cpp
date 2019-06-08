#include <network/tcp.hpp>
#include <exception/exception.hpp>

namespace tcp
{

Socket::Socket(const std::string& ip, const int port)
    : BaseSocket(SOCK_STREAM, ip.c_str(), port)
{
    ;
}

void Socket::listen(int maxConnetions)
{
    if (::listen(BaseSocket::getFd(), maxConnetions) != 0)
        throw Exception("Can't listen(): " +
                        std::string(::strerror(errno)), errno);
}

void Socket::connect()
{
    auto addr = BaseSocket::getAddr();
    if (::connect(BaseSocket::getFd(), (struct sockaddr* )&addr, sizeof(addr)) != 0)
        throw Exception("Can't connect(): " +
                        std::string(::strerror(errno)), errno);
}

int Socket::accept()
{
    struct sockaddr clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    auto clientFd = ::accept(BaseSocket::getFd(), &clientAddr, &addrLen);
    if (clientFd == -1)
        throw Exception("Can't accept(): " +
                        std::string(::strerror(errno)), errno);

    return clientFd;
}

void Socket::send(const int fd, DataProtocol &dataProtocol)
{
    auto [buf, len] = dataProtocol.serialize();
    if (::send(fd, buf, len, 0) == 0)
        throw Exception("Can't send(): " +
                        std::string(::strerror(errno)), errno);
}

ssize_t Socket::recv(const int fd, DataProtocol &dataProtocol)
{
    size_t len = 256;
    char buf[256] = { 0 };

    ssize_t bytes = ::recv(fd, buf, len, 0);
    if (bytes == -1)
        throw Exception("Can't recv(): " +
                        std::string(::strerror(errno)), errno);

    dataProtocol.deserialize(buf, len);
    return bytes;
}

}
