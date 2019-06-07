#include <service/client.hpp>

int tcp::Client::run()
{
    DataProtocol dataProtocol;

    socket_.connect();

    while (1)
    {
        dataProtocol.gather();
        socket_.send(dataProtocol);
    }

    return 0;
}

int udp::Client::run()
{
    DataProtocol dataProtocol;

    while (1)
    {
        dataProtocol.gather();
        socket_.send(dataProtocol);
    }

    return 0;
}
