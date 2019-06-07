#include <socket/socket.hpp>
#include <exception/exception.hpp>

Socket::Socket(const int type, const char* ip, const int port)
{
    try
    {
        fd_ = socket(AF_INET, type, 0); 
        if (fd_ == -1)
            throw "Can't create socket()";

        socketAddr_.sin_family      = AF_INET;
        socketAddr_.sin_addr.s_addr = ::inet_addr(ip);
        socketAddr_.sin_port        = ::htons(port);
    }
    catch (...)
    {
        ; // TODO: what now ??
    }
}

Socket::~Socket()
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

int Socket::getFd()
{
    return fd_;
}

struct sockaddr_in Socket::getAddr()
{
    return socketAddr_;
}

void Socket::bind()
{
    if (::bind(fd_, (sockaddr* )&socketAddr_, sizeof(socketAddr_)) != 0)
        throw Exception("Can't bind(): " + std::string(::strerror(errno)), errno);
}

void Socket::sendSockOpt()
{
    // TODO
}
