#include <socket/udp.hpp>

UdpSocket::UdpSocket() : Socket::Socket(SOCK_DGRAM, "127.0.0.1", 8080)
{
    ;
}

void UdpSocket::send(DataProtocol &dataProtocol)
{
	//auto [buf, len] = dataProtocol.serialize();
	// ssize_t sendto(int sockfd, const void *buf, size_t len,
	// int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
}

void UdpSocket::recv(DataProtocol &dataProtocol)
{
	// ssize_t recvfrom(int sockfd, void *buf, size_t len,
	// int flags, struct sockaddr *src_addr, socklen_t *addrlen);
}
