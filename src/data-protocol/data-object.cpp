#include <data-protocol/data-object.hpp>

#include <iostream>

DataObject::DataObject(std::string& name, std::unique_ptr<IData>& value)
    : name_(name), value_(std::move(value))
{
    ;
}

std::string DataObject::serialize()
{
    return std::string("{\"" + name_ + "\":" +
                       value_->serialize() + "}");
}

void DataObject::print()
{
    std::cout << "{";
    std::cout << name_ << ":";
    value_->print();
    std::cout << "}";
}

std::string DataObject::find(std::string& key)
{
    if (key.compare(name_) == 0)
        return DataObject::serialize();
    else
        return value_->find(key);
}