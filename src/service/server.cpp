#include <service/server.hpp>

#include <iostream>

namespace tcp
{

Server::Server(const std::string& ip, const int port)
{
    socket_ = std::make_unique<tcp::Socket>(ip, port);

    // Allows a socket descriptor to be reuseable
    socket_.get()->setOpt(SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT);

    socket_.get()->bind();
    socket_->listen(10);
}

int Server::run()
{
    std::cout << "[TCP::Server] Starting" << std::endl;

    DataProtocol dataProtocol;

    while (!signalHandler_.isExit())
    {
        socket_.get()->clearMonitorFdAll();

        for (auto i: connections_)
            socket_.get()->setMonitorFd(i.first);

        struct timeval timeout = {
            .tv_sec  = 60,
            .tv_usec = 0
        };

        if (socket_.get()->monitorFd(timeout) > 0)
        {
            if (socket_.get()->isMonitorFdReady())
            {
                std::cout << "[TCP::Server] New connection" << std::endl;
                connections_.insert(std::make_pair(socket_.get()->accept(), "client"));
            }

            auto it = connections_.begin();
            while (it != connections_.end())
            {
                if (Server::processConnection_(it->first))
                    it = connections_.erase(it);
                else
                    it++;
            }
        }
    }

    std::cout << "[TCP::Server] Closing" << std::endl;
    return 0;
}

int Server::processConnection_(const int fd)
{
    DataProtocol dataProtocol;

    if (!socket_.get()->isMonitorFdReady(fd))
        return 0;  

    if (socket_.get()->recv(fd, dataProtocol) == 0)
    {
        std::cout << "[TCP::Server] Closing connection" << std::endl;
        socket_.get()->close(fd);
        return 1;
    }
    else
    {
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
    socket_.get()->bind();
}

int Server::run()
{
    DataProtocol dataProtocol;

    while (!signalHandler_.isExit())
    {
        socket_.get()->recv(dataProtocol);

        dataProtocol.print();
    }

    return 0;
}

}
