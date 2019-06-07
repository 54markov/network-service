#pragma once

#include <socket/socket.hpp>
#include <data-protocol/data-protocol.hpp>

// Adapter
class UdpSocket : public Socket 
{
    public:
        UdpSocket();
        ~UdpSocket();

        int send(const DataProtocol &dataProtocol);
        int recv(DataProtocol &dataProtocol);
};