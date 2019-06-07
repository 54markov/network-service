#include <socket/udp.hpp>

UdpSocket::UdpSocket() : Socket::Socket(SOCK_DGRAM)
{
    ;
}

UdpSocket::~UdpSocket()
{
    ;
}

int UdpSocket::send(const DataProtocol &dataProtocol)
{
	// ssize_t sendto(int sockfd, const void *buf, size_t len,
	// int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
    return 0;
}

int UdpSocket::recv(DataProtocol &dataProtocol)
{
	// ssize_t recvfrom(int sockfd, void *buf, size_t len,
	// int flags, struct sockaddr *src_addr, socklen_t *addrlen);
    return 0;
}
