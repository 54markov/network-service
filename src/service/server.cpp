#include <service/server.hpp>

namespace tcp
{

Server::Server(const std::string& ip, const int port)
{
    socket_ = std::make_unique<tcp::Socket>(ip, port);
}

int Server::run()
{
    DataProtocol dataProtocol;

    socket_.get()->bind();
    socket_.get()->listen(10); // TODO

    while (!signalHandler_.isExit())
    {
        // TODO: select()
        //socket_.get()->accept();

        //socket_.get()->recv(dataProtocol);

        dataProtocol.print();
    }

    return 0;
}

}

namespace udp
{

Server::Server(const std::string& ip, const int port)
{
    socket_ = std::make_unique<udp::Socket>(ip, port);
}

int Server::run()
{
    DataProtocol dataProtocol;

    socket_.get()->bind();

    while (!signalHandler_.isExit())
    {
        socket_.get()->recv(dataProtocol);

        dataProtocol.print();
    }

    return 0;
}

}
