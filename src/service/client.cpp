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

        while (!signalHandler_.isExit())
        {
            std::cout << "[TCP::Client] Gathering data" << std::endl;
            dataProtocol.gather();
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
            dataProtocol.gather();
            std::cout << "[TCP::Client] Sending data" << std::endl;
            socket_.get()->send(/*fd,*/ dataProtocol);

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

}
