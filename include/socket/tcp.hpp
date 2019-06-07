#pragma once

#include <socket/socket.hpp>
#include <data-protocol/data-protocol.hpp>

// Adapter
class TcpSocket : public Socket 
{
    public:
        TcpSocket();
        ~TcpSocket() = default;

        void send(DataProtocol &dataProtocol);
        void recv(DataProtocol &dataProtocol);

        void listen(int maxConnections);
        void connect();
        void accept();

    private:
        int maxConnections_;
};
