#pragma once 

#include <network/udp.hpp>
#include <network/tcp.hpp>
#include <service/signal.hpp>

#include <string>
#include <memory>
#include <map>

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
        Server(const std::string& ip, const int port);
        ~Server();

        void run();

    private:
        SignalHandler signalHandler_;
        std::unique_ptr<tcp::Socket> socket_;
        std::map<int, std::string> connections_;

        bool processConnection_(const int fd);
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
        Server(const std::string& ip, const int port);
        ~Server() = default;

        void run();

    private:
        SignalHandler signalHandler_;
        std::unique_ptr<udp::Socket> socket_;
};

}
