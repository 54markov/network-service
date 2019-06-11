#include <data-protocol/data-protocol.hpp>

#include <iostream>

namespace Color
{
    const std::string red   = "\x1B[31m";
    const std::string green = "\x1B[32m";
    const std::string reset = "\x1B[0m";
};

int main(int argc, char const *argv[])
{
    const std::vector<std::string> test = {
        "{}",
        "{\"root\":\"value0\"}",
        "{\"root\":{\"key1\":\"value1\"}}",
        "{\"root\":[\"v0\",\"v0\"]}",
        "{\"root\":[[\"v0\",\"v0\"],[\"v0\",\"v0\"]]}",
        "{\"root\":{\"key1\":[\"v1\",\"v1\"]}}",
        "{\"root\":{\"key1\":[[\"v1\",\"v1\"],[\"v1\",\"v1\"]]}}",
        "{\"root\":[{\"key1\":[\"v1\",\"v1\"]},{\"key2\":[[\"v2\",\"v2\"],[\"v2\",\"v2\"]]}]}",
        "{\"root\":[{\"key1\":\"value1\"},{\"key2\":\"value2\"}]}",
        "{\"root\":[{\"key1\":[\"v1\",\"v1\"]},{\"key2\":\"value2\"}]}",
        "{\"root\":{\"k1\":{\"k2\":{\"k3\":{\"k4\":\"v4\"}}}}}",
        "{\"root\":{\"k1\":{\"k2\":{\"k3\":[{\"k4\":[\"v4\",\"v4\"]},{\"k5\":[\"v5\",\"v5\"]}]}}}}"
    };

    auto dataProtocol = DataProtocol();

    for (auto i : test)
    {
        std::cout << "Raw   : " << i << std::endl;

        dataProtocol.deserialize(i);

        auto serializeStr = dataProtocol.serialize();
        std::cout << "Serial: " << serializeStr << std::endl;

        std::cout << "Parsed: ";
        dataProtocol.print();

        std::cout << "Test - ";
        if (!i.compare(serializeStr))
            std::cout << Color::green << "Ok" << Color::reset << std::endl;
        else
            std::cout << Color::red << "Fail" << Color::reset << std::endl;
    }

    auto key = std::string("k5");
    std::cout << dataProtocol.find(key) << std::endl;

    return 0;
}
