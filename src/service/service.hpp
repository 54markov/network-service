#pragma once

#include <string>

template <typename T>
class Service : public T
{
    public:
        explicit Service(const std::string& ip, const int port) : T(ip, port) { }
        ~Service() = default;

        void run()
        {
            T::run();
        }
};
