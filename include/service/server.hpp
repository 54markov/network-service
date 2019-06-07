#pragma once 

#include <socket/udp.hpp>
#include <socket/tcp.hpp>

namespace tcp
{
    class Server
    {
        private:
            TcpSocket socket_;

        public:
            Server();
            ~Server();

            int run();
    };
}

namespace udp
{
    class Server
    {
        private:
            UdpSocket socket_;

        public:
            Server();
            ~Server();

            int run();
    };
}
