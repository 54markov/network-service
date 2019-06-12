#include <data-protocol/data-string.hpp>

#include <iostream>

DataString::DataString(std::string& string) : string_(string)
{
    ;
}

std::string DataString::serialize()
{
    return "\"" + string_ + "\"";
}

void DataString::print()
{
    std::cout << string_;
}

std::string DataString::find(std::string& key)
{
    // Not supproted
    return std::string("");
}