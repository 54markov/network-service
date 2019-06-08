#include <network/udp.hpp>

namespace udp
{

Socket::Socket(const std::string& ip, const int port)
    : BaseSocket(SOCK_STREAM, ip.c_str(), port)
{
    ;
}


void Socket::send(DataProtocol &dataProtocol)
{
	//auto [buf, len] = dataProtocol.serialize();
	// ssize_t sendto(int sockfd, const void *buf, size_t len,
	// int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
}

void Socket::recv(DataProtocol &dataProtocol)
{
	// ssize_t recvfrom(int sockfd, void *buf, size_t len,
	// int flags, struct sockaddr *src_addr, socklen_t *addrlen);
}

}