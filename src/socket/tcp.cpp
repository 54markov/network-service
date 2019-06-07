#include <socket/tcp.hpp>
#include <exception/exception.hpp>

TcpSocket::TcpSocket() : Socket::Socket(SOCK_STREAM, "127.0.0.1", 8080)
{
    ;
}

void TcpSocket::send(DataProtocol &dataProtocol)
{
    auto [buf, len] = dataProtocol.serialize();
    if (::send(Socket::getFd(), buf, len, 0) == 0)
        throw Exception("Can't send(): " + std::string(::strerror(errno)), errno);
}

void TcpSocket::recv(DataProtocol &dataProtocol)
{
    size_t len = 0;
    void *buf = nullptr;

    if (::recv(Socket::getFd(), buf, len, 0) != 0)
        throw Exception("Can't recv(): " + std::string(::strerror(errno)), errno);

    dataProtocol.deserialize();
}

void TcpSocket::listen(int maxConnextions)
{
    if (::listen(Socket::getFd(), maxConnextions) != 0)
        throw Exception("Can't listen(): " + std::string(::strerror(errno)), errno);
}

void TcpSocket::connect()
{
    auto addr = Socket::getAddr();
    if (::connect(Socket::getFd(), (struct sockaddr* )&addr, sizeof(addr)) != 0)
        throw Exception("Can't connect(): " + std::string(::strerror(errno)), errno);
}

void TcpSocket::accept()
{
    socklen_t addrLen;
    struct sockaddr clientAddr;

    auto clientFd = ::accept(Socket::getFd(), &clientAddr, &addrLen);
    if (clientFd == -1)
        throw Exception("Can't accept(): " + std::string(::strerror(errno)), errno);
}
