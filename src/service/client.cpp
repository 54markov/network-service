#include <service/client.hpp>

namespace tcp
{

Client::Client(const std::string& ip, const int port)
{
    socket_ = std::make_unique<tcp::Socket>(ip, port);
}

int Client::run()
{
    DataProtocol dataProtocol;

    socket_.get()->connect();

    while (!signalHandler_.isExit())
    {
        dataProtocol.gather();
        socket_.get()->send(dataProtocol);
    }

    return 0;
}

}

namespace udp
{

Client::Client(const std::string& ip, const int port)
{
    socket_ = std::make_unique<udp::Socket>(ip, port);
}

int Client::run()
{
    DataProtocol dataProtocol;

    while (!signalHandler_.isExit())
    {
        dataProtocol.gather();
        socket_.get()->send(dataProtocol);
    }

    return 0;
}

}
