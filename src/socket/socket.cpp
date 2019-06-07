#include <socket/socket.hpp>

Socket::Socket(int type)
{
    try
    {
        fd_ = socket(AF_INET, type, 0); 
        if (fd_ == -1)
            throw "Can't create socket()";
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
        ; // Do not propagte exception
    }
}

int Socket::getFd()
{
    return fd_;
}

void Socket::bind()
{
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    return;
}

void Socket::sendsockopt()
{
    // 
    return;
}