#include <service/service.hpp>
#include <service/server.hpp>
#include <service/client.hpp>

#include <iostream>

void usage(const char *arg)
{
    std::cerr << "Usage: ./" << arg << " [server/client]" << std::endl;
    ::exit(-1);
}

int main(int argc, char const *argv[])
{
    const auto ip = std::string("127.0.0.1");
    const auto port = 8080;

    if (argc < 2)
    {
        usage(argv[0]);
    }
    else
    {
        auto command = std::string(argv[1]);
        if (command.compare("server") == 0)
            Service<tcp::Server>(ip, port).run();
        else if (command.compare("client") == 0)
            Service<tcp::Client>(ip, port).run();
        else
            usage(argv[0]);
    }

    return 0;
}
