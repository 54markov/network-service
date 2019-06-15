#pragma once

#include <network/socket.hpp>
#include <data-protocol/data-protocol.hpp>

namespace udp
{

// Adapter to a Linux UDP socket
class Socket : public BaseSocket 
{
    public:
        Socket(const std::string& ip, const int port);
        ~Socket() = default;

        void send(DataProtocol &dataProtocol);
        void recv(DataProtocol &dataProtocol);
};

}