#pragma once

#include <data-protocol/data-protocol.hpp>

/*
 * A simple string value representation
 */
class DataString : public IData
{
    public:
        explicit DataString(std::string& string);
        ~DataString() = default;

        std::string serialize();
        void print();
        std::string find(std::string& key);

    private:
        std::string string_;
};