#pragma once

#include <network/socket.hpp>
#include <data-protocol/data-protocol.hpp>

// Adapter to Linux userspace network
namespace tcp
{

class Socket : public BaseSocket 
{
    public:
        explicit Socket(const std::string& ip, const int port);
        ~Socket() = default;

        void listen(int maxConnections);
        void connect();
        int accept();

        void send(const int fd, DataProtocol& dataProtocol);
        ssize_t recv(const int fd, DataProtocol& dataProtocol);
};

}
