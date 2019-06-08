#pragma once

#include <tuple>
#include <string>

class DataProtocol
{
    public:
        DataProtocol() = default;
        ~DataProtocol() = default;

        std::tuple<const char*, size_t> serialize();
        void deserialize(const char* buf, const size_t size);

        void gather();
        void print();

    private:
    	std::string str_;
};
