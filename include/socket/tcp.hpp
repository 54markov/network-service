#pragma once

#include <socket/socket.hpp>
#include <data-protocol/data-protocol.hpp>

// Adapter
class TcpSocket : public Socket 
{
    public:
        TcpSocket();
        ~TcpSocket();

        int send(const DataProtocol &dataProtocol);
        int recv(DataProtocol &dataProtocol);

        int listen();
        int connect();
        int accept();
};
