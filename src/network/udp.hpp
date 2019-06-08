#pragma once

#include <network/socket.hpp>
#include <data-protocol/data-protocol.hpp>

namespace udp
{

// Adapter to Linux userspace network
class Socket : public BaseSocket 
{
    public:
        explicit Socket(const std::string& ip, const int port);
        ~Socket() = default;

        void send(DataProtocol &dataProtocol);
        void recv(DataProtocol &dataProtocol);
};

}