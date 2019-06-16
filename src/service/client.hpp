#pragma once 

#include <network/udp.hpp>
#include <network/tcp.hpp>
#include <service/signal.hpp>

#include <memory>

namespace tcp
{

/******************************************************************************/
/* create   : Socket                                                          */
/*              |                                                             */
/* to server: Connect                                                         */
/*              |                                                             */
/* routine  : Send/Recv                                                       */
/*              |                                                             */
/* close    : Socket                                                          */
/******************************************************************************/
class Client
{
    public:
        Client(const std::string& ip, const int port);
        ~Client() = default;

        int run();

    private:
        SignalHandler signalHandler_;
        std::unique_ptr<tcp::Socket> socket_;

        bool isConnected(const int fd);
};

}

namespace udp
{

/******************************************************************************/
/* create   : Socket                                                          */
/*              |                                                             */
/* routine  : Send/Recv                                                       */
/*              |                                                             */
/* close    : Socket                                                          */
/******************************************************************************/
class Client
{
   public:
        Client(const std::string& ip, const int port);
        ~Client() = default;

        int run();

    private:
        SignalHandler signalHandler_;
        std::unique_ptr<udp::Socket> socket_;
};

}
