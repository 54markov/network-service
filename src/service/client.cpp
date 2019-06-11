#include <service/client.hpp>
#include <exception/exception.hpp>

#include <iostream>
#include <thread>
#include <chrono>

namespace tcp
{

Client::Client(const std::string& ip, const int port)
{
    socket_ = std::make_unique<tcp::Socket>(ip, port);
}

int Client::run()
{
    std::cout << "[TCP::Client] Starting" << std::endl;
    DataProtocol dataProtocol;

    try {
        std::cout << "[TCP::Client] Connecting" << std::endl;
        socket_.get()->connect();

        auto fd = socket_.get()->getFd();
        socket_.get()->setNonBlocking(fd);

        while (!signalHandler_.isExit())
        {
            if (Client::isConnected(fd))
            {
                std::cout << "[TCP::Client] Server is hang up" << std::endl;
                break;
            }

            std::cout << "[TCP::Client] Gathering data" << std::endl;
            auto cpuUsage = CpuMonitor().getUsage();
            dataProtocol.build(cpuUsage);
            std::cout << "[TCP::Client] Sending data" << std::endl;
            socket_.get()->send(fd, dataProtocol);

            // Simulates a some important work here
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch(Exception& exception)
    {
        std::cerr << exception.what() << std::endl;
    }

    std::cout << "[TCP::Client] Closing" << std::endl;
    return 0;
}

bool Client::isConnected(const int fd)
{
    if (socket_.get()->check(fd) == 0)
        return true;
    else
        return false;
}

}

namespace udp
{

Client::Client(const std::string& ip, const int port)
{
    // TODO
}

int Client::run()
{
    // TODO
    return 0;
}

}
