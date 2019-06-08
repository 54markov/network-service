#include <network/socket.hpp>
#include <exception/exception.hpp>

BaseSocket::BaseSocket(int type, const char* ip, int port)
{
    fd_ = socket(AF_INET, type, 0); // TODO
    if (fd_ == -1)
        throw Exception("Can't create socket(): " +
                        std::string(::strerror(errno)), errno);

    socketAddr_.sin_family      = AF_INET;
    socketAddr_.sin_addr.s_addr = ::inet_addr(ip);
    socketAddr_.sin_port        = ::htons(port);
}

BaseSocket::~BaseSocket()
{
    try
    {
        ::close(fd_);
    }
    catch(...)
    {
        ; // Do not propagate exception
    }
}

int BaseSocket::getFd()
{
    return fd_;
}

struct sockaddr_in BaseSocket::getAddr()
{
    return socketAddr_;
}

void BaseSocket::bind()
{
    if (::bind(fd_, (sockaddr* )&socketAddr_, sizeof(socketAddr_)) != 0)
        throw Exception("Can't bind(): " + std::string(::strerror(errno)), errno);
}

void BaseSocket::sendSockOpt()
{
    // int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);  
}
