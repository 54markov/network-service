#pragma once

#include <tuple>

class DataProtocol
{
    public:
        DataProtocol();
        ~DataProtocol();

        std::tuple<char*, size_t> serialize();
        void deserialize();

        void gather();
        void print();
};
