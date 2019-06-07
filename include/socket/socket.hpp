#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

// A sokcet base class
class Socket
{
    private:
        int fd_;
        struct sockaddr_in socketAddr_;

    public:
        explicit Socket(const int type, const char* ip, const int port);
        ~Socket();

        int getFd();
        struct sockaddr_in getAddr();

        void bind();
        void sendSockOpt();
};
