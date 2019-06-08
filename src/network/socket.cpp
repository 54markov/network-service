#include <network/socket.hpp>
#include <exception/exception.hpp>

BaseSocket::BaseSocket(int type, const char* ip, int port)
{
    fd_ = socket(AF_INET, type, 0); // TODO
    if (fd_ == -1)
        throw Exception("Can't create socket(): " +
                        std::string(::strerror(errno)), errno);

    address_.sin_family      = AF_INET;
    address_.sin_addr.s_addr = ::inet_addr(ip);
    address_.sin_port        = ::htons(port);
}

BaseSocket::~BaseSocket()
{
    try
    {
        BaseSocket::close(fd_);
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
    return address_;
}

void BaseSocket::bind()
{
    if (::bind(fd_, reinterpret_cast<struct sockaddr *>(&address_),
               sizeof(address_)) != 0)
        throw Exception("Can't bind(): " +
                        std::string(::strerror(errno)), errno);
}

void BaseSocket::close(const int fd)
{
    ::close(fd);
}

void BaseSocket::setOpt(const int level, const int options)
{
    const auto on = 1; 
    if (::setsockopt(fd_, level, options, &on, sizeof(on)) < 0)
        throw Exception("Can't setsockopt(): " +
                        std::string(::strerror(errno)), errno);
}

void BaseSocket::setNonBlocking()
{
    BaseSocket::setNonBlocking(fd_);
}

void BaseSocket::setNonBlocking(const int fd)
{
    auto opts = ::fcntl(fd, F_GETFL, 0);
    if (opts < 0)
        throw Exception("Can't get socket flags: " +
                        std::string(::strerror(errno)), errno);

    opts = (opts | O_NONBLOCK);

    if (::fcntl(fd, F_SETFL, opts) < 0)
        throw Exception("Can't set socket to non-blocking state" +
                        std::string(::strerror(errno)), errno);
}

#include <iostream>

int BaseSocket::monitorFd(struct timeval& timeout)
{
    /*
     * Allow to monitor multiple file descriptors,
     * waiting until one or more of the file descriptors
     * become "ready" for some class of I/O operation
     */
    auto fds = ::select(highFd_ + 1, &(setFd_), reinterpret_cast<fd_set*>(0),
                        reinterpret_cast<fd_set*>(0), &timeout);
    if (fds == -1 && !EINTR)
        throw Exception("Can't ::select()" +
                        std::string(::strerror(errno)), errno);

    return fds;
}

bool BaseSocket::isMonitorFdReady()
{
    return BaseSocket::isMonitorFdReady(fd_);
}

bool BaseSocket::isMonitorFdReady(const int fd)
{
    return FD_ISSET(fd, &(this->setFd_));
}

void BaseSocket::setMonitorFd(const int fd)
{
    if (fd != 0)
    {
        // Adds the socket file descriptor to the monitoring for select()
        FD_SET(fd, &(setFd_));

        // We need the highest socket for select()
        if (fd > highFd_)
            highFd_ = fd;
    }
}

void BaseSocket::clearMonitorFd(const int fd)
{
    if (fd != 0)
        FD_CLR(fd, &(this->setFd_));
}

void BaseSocket::clearMonitorFdAll()
{
    highFd_ = fd_;
    FD_ZERO(&(setFd_));
    FD_SET(fd_, &(setFd_));
}
