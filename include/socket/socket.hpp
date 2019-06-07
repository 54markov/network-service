#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

// A sokcet base class
class Socket
{
    private:
        int fd_;

    public:
        explicit Socket(int type);
        ~Socket();

        int getFd();

        void bind();
        void sendsockopt();
};
