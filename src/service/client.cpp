#include <service/client.hpp>
#include <exception/exception.hpp>

#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

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
            dataProtocol.gather1();
            std::cout << "[TCP::Client] Sending data" << std::endl;
            socket_.get()->send(fd, dataProtocol);
            std::cout << "[TCP::Client] Gathering data" << std::endl;
            dataProtocol.gather2();
            std::cout << "[TCP::Client] Sending data" << std::endl;
            socket_.get()->send(fd, dataProtocol);

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
    socket_ = std::make_unique<udp::Socket>(ip, port);
}

int Client::run()
{
    std::cout << "[TCP::Client] Starting" << std::endl;
    DataProtocol dataProtocol;

    try {
        //auto fd = socket_.get()->getFd();
    
        while (!signalHandler_.isExit())
        {
            std::cout << "[TCP::Client] Gathering data" << std::endl;
            dataProtocol.gather1();
            std::cout << "[TCP::Client] Sending data" << std::endl;
            socket_.get()->send(dataProtocol);

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch(Exception& exception)
    {
        std::cerr << exception.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unhanlde exception" << std::endl;
    }

    std::cout << "[TCP::Client] Closing" << std::endl;
    return 0;
}

}
