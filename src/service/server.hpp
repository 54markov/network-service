#pragma once 

#include <network/udp.hpp>
#include <network/tcp.hpp>
#include <service/signal.hpp>

#include <memory>

namespace tcp
{

/******************************************************************************/
/* create  : Socket                                                           */
/*             |                                                              */
/*           Bind                                                             */
/*             |                                                              */
/*           Listen                                                           */
/*             |                                                              */
/*           Accept                                                           */
/*             |                                                              */
/* routine : Send/Recv                                                        */
/*             |                                                              */
/* close   : Socket                                                           */
/******************************************************************************/
class Server
{
    public:
        explicit Server(const std::string& ip, const int port);
        ~Server() = default;

        int run();

    private:
        SignalHandler signalHandler_;
        std::unique_ptr<tcp::Socket> socket_;
};

}

namespace udp
{

/******************************************************************************/
/* create  : Socket                                                           */
/*             |                                                              */
/*           Bind                                                             */
/*             |                                                              */
/* routine : Send/Recv                                                        */
/*             |                                                              */
/* close   : Socket                                                           */
/******************************************************************************/
class Server
{
    public:
        explicit Server(const std::string& ip, const int port);
        ~Server() = default;

        int run();

    private:
        SignalHandler signalHandler_;
        std::unique_ptr<udp::Socket> socket_;
};

}
