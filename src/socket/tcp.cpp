#include <socket/tcp.hpp>

TcpSocket::TcpSocket() : Socket::Socket(SOCK_STREAM)
{
    ;
}

TcpSocket::~TcpSocket()
{
    ;
}

int TcpSocket::send(const DataProtocol &dataProtocol)
{
    // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
    return 0;
}

int TcpSocket::recv(DataProtocol &dataProtocol)
{
    // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    return 0;
}

int TcpSocket::listen()
{
    // int listen(int sockfd, int backlog)
    return 0;
}

int TcpSocket::connect()
{
    // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    return 0;
}

int TcpSocket::accept()
{
    // int accept(int s, struct sockaddr *addr, socklen_t *addrlen)
    return 0;
}
