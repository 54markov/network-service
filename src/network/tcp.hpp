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

        void send(DataProtocol& dataProtocol);
        void recv(DataProtocol& dataProtocol);

        void listen(int maxConnections);
        void connect();
        void accept();

    private:
        int maxConnections_;
};

}
