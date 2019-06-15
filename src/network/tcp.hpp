#pragma once

#include <network/socket.hpp>
#include <data-protocol/data-protocol.hpp>

namespace tcp
{

// Adapter to a Linux TCP socket
class Socket : public BaseSocket 
{
    public:
        Socket(const std::string& ip, const int port);
        ~Socket() = default;

        void listen(int maxConnections);
        void connect();
        int accept();

        void send(const int fd, DataProtocol& dataProtocol);
        ssize_t recv(const int fd, DataProtocol& dataProtocol);

        ssize_t check(const int fd);
};

}
