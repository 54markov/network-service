#include <data-protocol/data-protocol.hpp>
#include <data-protocol/data-string.hpp>
#include <data-protocol/data-object.hpp>
#include <data-protocol/data-array.hpp>

#include <iostream>

std::string DataProtocol::serialize()
{
    if (data_.get() != nullptr)
        return data_.get()->serialize();
    else
        return std::string("{}");
}

void DataProtocol::print()
{
    if (data_.get() != nullptr)
    {
        data_.get()->print();
        std::cout << std::endl;
    }
    else
    {
        std::cout << "{}" << std::endl;
    }
}

void DataProtocol::deserialize(std::string string)
{
    auto deleted = std::move(data_);
    data_ = std::move(DataProtocol::parse_(string));
}


void DataProtocol::build(std::vector<CpuData>& v)
{
    auto deleted = std::move(data_);

    std::string root = "Cpu usage";

    auto dataArray = std::make_unique<DataArray>();

    for (auto i : v)
    {
        std::string cpu = i.name;
        std::string usage = std::to_string(i.usage);
        std::unique_ptr<IData> value =
            std::make_unique<DataString>(usage);
        std::unique_ptr<IData> object =
            std::make_unique<DataObject>(cpu, value);
        dataArray.get()->add(object);
    }

    std::unique_ptr<IData> iArray = std::move(dataArray);
    std::unique_ptr<IData> iObject = std::make_unique<DataObject>(root, iArray);

    data_ = std::move(iObject);
}

std::string DataProtocol::find(std::string& key)
{
    if (data_.get() != nullptr)
        return data_.get()->find(key);
    else
        return std::string("{}");
}

std::vector<std::string> DataProtocol::split_(std::string s, const std::string& delimiter)
{
    size_t pos = 0;

    std::vector<std::string> tokens;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        if (delimiter != ",")
            token = s.substr(0, pos + 1);
        else
            token = s.substr(0, pos);

        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    tokens.push_back(s);
    return tokens;
}

std::unique_ptr<IData> DataProtocol::parseObject_(std::string string)
{
    if (string.length() == 0)
        return nullptr;

    //std::cout << "Object: " << string << std::endl;

    string.erase(string.begin());
    string.erase(string.end() - 1);

    if (string.length() == 0)
        return nullptr; // An empty IData

    std::size_t found = string.find(":");
    std::string key = std::string(string.begin(), string.begin() + found);
    std::string value = std::string(string.begin() + found + 1, string.end());

    key.erase(key.begin());
    key.erase(key.end() - 1);

    if (value[0] != '\"')
    {
        std::unique_ptr<IData> newValue = DataProtocol::parse_(value);
        return std::make_unique<DataObject>(key, newValue);
    }
    else
    {
        value.erase(value.begin());
        value.erase(value.end() - 1);

        std::unique_ptr<IData> newValue = std::make_unique<DataString>(value);
        return std::make_unique<DataObject>(key, newValue);
    }

    return nullptr; // An empty IData
}

std::unique_ptr<IData> DataProtocol::parseArray_(std::string string)
{
    if (string.length() == 0)
        return nullptr; // An empty IData

    auto dataArray = std::make_unique<DataArray>();

    string.erase(string.begin());
    string.erase(string.end() - 1);

    std::string delimiter;

    if (string[0] == '{')
    {
        delimiter = "},";
    }
    else if (string[0] == '[')
    {
        delimiter = "],";
    }
    else
    {
        delimiter = ",";
    }

    for (auto i : DataProtocol::split_(string, delimiter))
    {
        if (delimiter != ",")
        {
            auto entry = DataProtocol::parse_(i);
            dataArray.get()->add(entry);
        }
        else
        {
            std::string value = i;
            value.erase(value.begin());
            value.erase(value.end() - 1);

            std::unique_ptr<IData> entry = std::make_unique<DataString>(value);
            dataArray.get()->add(entry);
        }
    }

    return dataArray;
}

std::unique_ptr<IData> DataProtocol::parse_(std::string string)
{
    if (string.length() == 0)
        return nullptr; // An empty IData

    switch (string[0])
    {
        case '{': return DataProtocol::parseObject_(string);
        case '[': return DataProtocol::parseArray_(string);
        default: break;
    }

    return nullptr; // An empty IData
}
