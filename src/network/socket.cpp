#include <network/socket.hpp>
#include <exception/exception.hpp>

#include <iostream>

BaseSocket::BaseSocket(int type, int port, const char* ip)
{
    fd_ = socket(AF_INET, type, 0);
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
    catch(Exception& exception)
    {
        std::cerr << exception.what() << std::endl;
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
    /*
     * The reinterpret_cast operator changes a pointer
     * to any other type of pointer.
     */
    if (::bind(fd_, reinterpret_cast<struct sockaddr *>(&address_),
               sizeof(address_)) != 0)
        throw Exception("Can't bind(): " +
                        std::string(::strerror(errno)), errno);
}

void BaseSocket::close(const int fd)
{
    if (::close(fd) == -1)
        throw Exception("Can't close socket(): " +
                        std::string(::strerror(errno)), errno);
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
    if (fd < 0)
        throw Exception("Can't set to non-blocking: not valid fd", -1);

    auto opts = ::fcntl(fd, F_GETFL, 0);
    if (opts < 0)
        throw Exception("Can't get socket flags: " +
                        std::string(::strerror(errno)), errno);

    opts = (opts | O_NONBLOCK);

    if (::fcntl(fd, F_SETFL, opts) < 0)
        throw Exception("Can't set to non-blocking state: " +
                        std::string(::strerror(errno)), errno);
}

int BaseSocket::monitorFd(struct timeval& timeout)
{
    /*
     * Allow to monitor multiple file descriptors,
     * waiting until one or more of the file descriptors
     * become "ready" for some class of I/O operation
     */
    auto fds = ::select(highFd_ + 1, &(monitorFd_), nullptr, nullptr, &timeout);
    if (fds == -1 && !EINTR)
        throw Exception("Can't select(): " +
                        std::string(::strerror(errno)), errno);

    return fds;
}

bool BaseSocket::isMonitorFdReady()
{
    return BaseSocket::isMonitorFdReady(fd_);
}

bool BaseSocket::isMonitorFdReady(const int fd)
{
    if (fd < 0)
        throw Exception("Can't check: not valid fd", -1);

    return FD_ISSET(fd, &(monitorFd_));
}

void BaseSocket::setMonitorFd(const int fd)
{
    if (fd < 0)
        throw Exception("Can't set: not valid fd", -1);

    // Adds the socket file descriptor to the monitoring for select()
    FD_SET(fd, &(monitorFd_));

    // We need the highest socket for select()
    if (fd > highFd_)
        highFd_ = fd;
}

void BaseSocket::clearMonitorFd(const int fd)
{
    if (fd < 0)
        throw Exception("Can't clear: not valid fd", -1);

    FD_CLR(fd, &(monitorFd_));
}

void BaseSocket::clearMonitorFdAll()
{
    highFd_ = fd_;
    FD_ZERO(&(monitorFd_));
    FD_SET(fd_, &(monitorFd_));
}
