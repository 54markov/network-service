#include <service/service.hpp>
#include <service/server.hpp>
#include <service/client.hpp>

int main(int argc, char const *argv[])
{
    auto is_server = true;

    if (is_server)
    {
        auto sever = Service<tcp::Server>();
        sever.run();
    }
    else
    {
        auto client = Service<tcp::Client>();
        client.run();
    }

    return 0;
}
