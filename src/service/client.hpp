#pragma once 

#include <network/udp.hpp>
#include <network/tcp.hpp>

#include <memory>

namespace tcp
{

/******************************************************************************/
/* create   : Socket                                                          */
/*               |                                                            */
/* to server: Connect                                                         */
/*               |                                                            */
/* routine  : Send/Recv                                                       */
/*               |                                                            */
/* close    : Socket                                                          */
/******************************************************************************/
class Client
{
    public:
        explicit Client(const std::string& ip, const int port);
        ~Client() = default;

        int run();

    private:
        std::unique_ptr<tcp::Socket> socket_;
};

}

namespace udp
{

/******************************************************************************/
/* create   : Socket                                                          */
/*               |                                                            */
/* routine  : Send/Recv                                                       */
/*               |                                                            */
/* close    : Socket                                                          */
/******************************************************************************/
class Client
{
   public:
        explicit Client(const std::string& ip, const int port);
        ~Client() = default;

        int run();

    private:
        std::unique_ptr<udp::Socket> socket_;
};

}
