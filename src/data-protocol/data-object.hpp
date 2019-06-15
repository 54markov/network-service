#pragma once

#include <data-protocol/data-protocol.hpp>

/*
 * An object is name/value pair.
 * An object begins with "{" and ends with "}".
 */
class DataObject : public IData
{
    public:
        DataObject(std::string& name, std::unique_ptr<IData>& value);
        ~DataObject() = default;

        std::string serialize();
        void print();
        std::string find(std::string& key);

    private:
        std::string name_;
        std::unique_ptr<IData> value_;
};
