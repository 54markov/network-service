#include <service/service.hpp>
#include <service/server.hpp>
#include <service/client.hpp>

int main(int argc, char const *argv[])
{
    const auto ip = std::string("127.0.0.1");
    const auto port = 8080;

    auto is_server = false;

    if (is_server)
    {
        auto sever = Service<tcp::Server>(ip, port);
        sever.run();
    }
    else
    {
        auto client = Service<tcp::Client>(ip, port);
        client.run();
    }

    return 0;
}
