#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

// A base socket class
class BaseSocket
{
    public:
        BaseSocket(int type, int port, const char* ip);
        virtual ~BaseSocket();

        int getFd();
        struct sockaddr_in getAddr();

        void bind();
        void close(const int fd);

        void setOpt(const int level, const int options);

        void setNonBlocking();
        void setNonBlocking(const int fd);

        int monitorFd(struct timeval& timeout);

        bool isMonitorFdReady();
        bool isMonitorFdReady(const int fd);

        void setMonitorFd(const int fd);
        void clearMonitorFd(const int fd);
        void clearMonitorFdAll();

    private:
        int fd_;                     // Self fd
        int highFd_;                 // Highest fd
        fd_set monitorFd_;           // Monitoring fd
        struct sockaddr_in address_; // Socket address
};
