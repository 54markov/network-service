#pragma once

#include <string>

class IData
{
    public:
        virtual ~IData() = default;

        virtual std::string serialize() = 0;
        virtual void print() = 0;
        virtual std::string find(std::string& key) = 0;
};
