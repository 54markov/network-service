#pragma once

#include <socket/socket.hpp>
#include <data-protocol/data-protocol.hpp>

// Adapter
class UdpSocket : public Socket 
{
    public:
        UdpSocket();
        ~UdpSocket() = default;

        void send(DataProtocol &dataProtocol);
        void recv(DataProtocol &dataProtocol);
};