#pragma once

#include <data-protocol/data-protocol.hpp>

/*
 * An array is an ordered collection of values.
 * An array begins with "[" and ends with "]".
 * Values are separated by ",".
 */
class DataArray : public IData
{
    public:
        DataArray() = default;
        ~DataArray() = default;

        std::string serialize();
        void print();
        std::string find(std::string& key);

        void add(std::unique_ptr<IData>& data);

    private:
        std::vector<std::unique_ptr<IData>> array_;
};
