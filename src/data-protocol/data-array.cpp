#include <data-protocol/data-array.hpp>

#include <iostream>

void DataArray::add(std::unique_ptr<IData>& data)
{
    array_.push_back(std::move(data));
}

std::string DataArray::serialize()
{
    std::string string = "[";
    for (auto i = 0; i < (int)array_.size(); i++)
    {
        string += array_[i]->serialize();
        if (i < (int)array_.size() - 1)
            string += ",";
    }
    string += "]";
    return string;
}

void DataArray::print()
{
    std::cout << "[";
    for (auto i = 0; i < (int)array_.size(); i++)
    {
        array_[i]->print();
        if (i < (int)array_.size() - 1)
            std::cout << ",";
    }
    std::cout << "]";
}

std::string DataArray::find(std::string& key)
{
    std::string string;

    for (auto i = 0; i < (int)array_.size(); i++)
    {
        string = array_[i]->find(key);
        if (string != "")
            return string;
    }

    return std::string("");
}
