#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

// A socket base class
class BaseSocket
{
    private:
        int fd_;
        struct sockaddr_in socketAddr_;

    public:
        explicit BaseSocket(int type, const char* ip, int port);
        ~BaseSocket();

        int getFd();
        struct sockaddr_in getAddr();

        void bind();
        void sendSockOpt();
};
