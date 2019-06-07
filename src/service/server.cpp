#include <service/server.hpp>

int tcp::Server::run()
{
    DataProtocol dataProtocol;

    socket_.bind();
    socket_.listen(10);

    while (1)
    {
        // TODO: select()
        socket_.accept();

        socket_.recv(dataProtocol);

        dataProtocol.print();
    }

    return 0;
}

int udp::Server::run()
{
    DataProtocol dataProtocol;

    socket_.bind();

    while (1)
    {
        socket_.recv(dataProtocol);

        dataProtocol.print();
    }

    return 0;
}
