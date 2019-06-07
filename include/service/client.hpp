#pragma once 

#include <socket/udp.hpp>
#include <socket/tcp.hpp>

namespace tcp
{
    class Client
    {
        private:
            TcpSocket socket_;

        public:
            Client() = default;
            ~Client() = default;

            int run();
    };
}

namespace udp
{
    class Client
    {
        private:
            UdpSocket socket_;

        public:
            Client() = default;
            ~Client() = default;

            int run();
    };
}
