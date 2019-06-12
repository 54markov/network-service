#include <network/tcp.hpp>
#include <exception/exception.hpp>

#include <iostream>

namespace tcp
{

Socket::Socket(const std::string& ip, const int port)
    : BaseSocket(SOCK_STREAM, port, ip.c_str())
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
    if (::connect(BaseSocket::getFd(),
                  reinterpret_cast<struct sockaddr *>(&addr),
                  sizeof(addr)) != 0)
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
    if (fd < 0)
        throw Exception("Can't send(): not valid fd", -1);

    auto str = dataProtocol.serialize();
    if (::send(fd, str.c_str(), str.length(), 0) == 0)
        throw Exception("Can't send(): " +
                        std::string(::strerror(errno)), errno);
}

ssize_t Socket::recv(const int fd, DataProtocol &dataProtocol)
{
    if (fd < 0)
        throw Exception("Can't recv(): not valid fd", -1);

    size_t len = 256;
    char buf[256] = { 0 };

    ssize_t bytes = ::recv(fd, buf, len, 0);
    if (bytes == -1)
        throw Exception("Can't recv(): " +
                        std::string(::strerror(errno)), errno);

    dataProtocol.deserialize(std::string(buf));
    return bytes;
}

ssize_t Socket::check(const int fd)
{
    if (fd < 0)
        throw Exception("Can't check(): not valid fd", -1);

    char buf[1] = { 0 };
    return ::recv(fd, buf, 1, MSG_PEEK | MSG_DONTWAIT);
    // Afterwards, you must check errno if it fails.
    // It can fail with EAGAIN or it can fail with EBADF or ENOTCONN etc.
}

}
