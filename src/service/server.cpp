#include <service/server.hpp>
#include <exception/exception.hpp>

#include <iostream>

namespace tcp
{

Server::Server(const std::string& ip, const int port)
{
    socket_ = std::make_unique<tcp::Socket>(ip, port);

    // Allows a socket descriptor to be reuseable
    socket_.get()->setOpt(SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT);

    socket_.get()->bind();
    socket_->listen(10); // Only 10 clients allowed
}

Server::~Server()
{
    for (auto i : connections_)
        socket_.get()->close(i.first);
}

void Server::run()
{
    std::cout << "[TCP::Server] Starting" << std::endl;

    DataProtocol dataProtocol;

    try
    {
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
                    auto fd = socket_.get()->accept();
                    std::cout << "[TCP::Server] A new connection, fd " << fd << std::endl;
                    connections_.insert(std::make_pair(fd, ""));
                }

                auto it = connections_.begin();
                while (it != connections_.end())
                {
                    if (!Server::processConnection_(it->first))
                        it = connections_.erase(it);
                    else
                        it++;
                }
            }
        }
    }
    catch(Exception& exception)
    {
        std::cerr << exception.what() << std::endl;
    }

    std::cout << "[TCP::Server] Closing" << std::endl;
}

bool Server::processConnection_(const int fd)
{
    if (!socket_.get()->isMonitorFdReady(fd))
        return true;

    DataProtocol dataProtocol;
    if (socket_.get()->recv(fd, dataProtocol) == 0)
    {
        std::cout << "[TCP::Server] Closing connection, fd " << fd << std::endl;
        socket_.get()->close(fd);
        return false;
    }

    dataProtocol.print();

    return true;
}

}

namespace udp
{

Server::Server(const std::string& ip, const int port)
{
    // TODO
}

void Server::run()
{
    // TODO
}

}
