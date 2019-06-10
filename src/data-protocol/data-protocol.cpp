#include <data-protocol/data-protocol.hpp>

#include <iostream>

DataPair::DataPair(std::string name, std::unique_ptr<IData>& data)
{
    name_ = name;
    value_ = std::move(data);
}

void DataPair::print()
{
    std::cout << name_ << ":";
    value_->print();
}

std::string DataPair::serialize()
{
    return "\"" + name_ + "\"" + ":" + value_->serialize();
}

DataString::DataString(std::string string)
{
    string_ = string;
}

void DataString::print()
{
    std::cout << string_;
}

std::string DataString::serialize()
{
    return "\"" + string_ + "\"";
}

void DataArray::add(std::unique_ptr<IData>& data)
{
    array_.push_back(std::move(data));
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

DataObject::DataObject(std::unique_ptr<IData>& data)
{
    pairs_.push_back(std::move(data));
}

void DataObject::add(std::unique_ptr<IData>& data)
{
    pairs_.push_back(std::move(data));
}

void DataObject::print()
{
    std::cout << "{";
    for (auto i = 0; i < (int)pairs_.size(); i++)
    {
        pairs_[i]->print();
        if (i < (int)pairs_.size() - 1)
            std::cout << ",";
    }
    std::cout << "}";
}

std::string DataObject::serialize()
{
    std::string string = "{";
    for (auto i = 0; i < (int)pairs_.size(); i++)
    {
        string += pairs_[i]->serialize();
        if (i < (int)pairs_.size() - 1)
            string += ",";
    }
    string += "}";
    return string;
}

std::string DataProtocol::serialize()
{
    if (data_.get() != nullptr)
        return data_.get()->serialize();
    else
        return std::string("{}");
}

void DataProtocol::deserialize(std::string string)
{
    auto deleted = std::move(data_);
    data_ = std::move(DataProtocol::parse_(string));
}

void DataProtocol::gather1()
{
    auto deleted = std::move(data_);

    std::unique_ptr<IData> value1 = std::make_unique<DataString>("40%");
    std::unique_ptr<IData> value2 = std::make_unique<DataString>("50%");
    std::unique_ptr<IData> value3 = std::make_unique<DataString>("60%");
    std::unique_ptr<IData> value4 = std::make_unique<DataString>("70%");

    std::unique_ptr<IData> pair1 = std::make_unique<DataPair>("CPU1", value1);
    std::unique_ptr<IData> pair2 = std::make_unique<DataPair>("CPU2", value2);
    std::unique_ptr<IData> pair3 = std::make_unique<DataPair>("CPU3", value3);
    std::unique_ptr<IData> pair4 = std::make_unique<DataPair>("CPU4", value4);

    std::unique_ptr<IData> obj1 = std::make_unique<DataObject>(pair1);
    std::unique_ptr<IData> obj2 = std::make_unique<DataObject>(pair2);
    std::unique_ptr<IData> obj3 = std::make_unique<DataObject>(pair3);
    std::unique_ptr<IData> obj4 = std::make_unique<DataObject>(pair4);

    auto dataArray = std::make_unique<DataArray>();
    dataArray.get()->add(obj1);
    dataArray.get()->add(obj2);
    dataArray.get()->add(obj3);
    dataArray.get()->add(obj4);

    std::unique_ptr<IData> iDataArray = std::move(dataArray);

    std::unique_ptr<IData> root = std::make_unique<DataPair>("System usage", iDataArray);

    data_ = std::make_unique<DataObject>(root);
}

void DataProtocol::gather2()
{
    auto deleted = std::move(data_);

    std::unique_ptr<IData> valuePid1 = std::make_unique<DataString>("1234");
    std::unique_ptr<IData> pairPid1 = std::make_unique<DataPair>("PID", valuePid1);
    std::unique_ptr<IData> objPid1 = std::make_unique<DataObject>(pairPid1);

    std::unique_ptr<IData> valuePerYes = std::make_unique<DataString>("yes");
    std::unique_ptr<IData> pairPerYes = std::make_unique<DataPair>("Read", valuePerYes);
    std::unique_ptr<IData> objPerYes = std::make_unique<DataObject>(pairPerYes);

    std::unique_ptr<IData> valuePerNo = std::make_unique<DataString>("no");
    std::unique_ptr<IData> pairPerNo = std::make_unique<DataPair>("Write", valuePerNo);
    std::unique_ptr<IData> objPerNo = std::make_unique<DataObject>(pairPerNo);

    auto array0 = std::make_unique<DataArray>();
    array0.get()->add(objPerYes);
    array0.get()->add(objPerNo);

    std::unique_ptr<IData> iArray0 = std::move(array0);
    std::unique_ptr<IData> pair1 = std::make_unique<DataPair>("Permissions", iArray0);
    std::unique_ptr<IData> obj1 = std::make_unique<DataObject>(pair1);

    std::unique_ptr<IData> pair2 = std::make_unique<DataPair>("Process", objPid1);
    std::unique_ptr<IData> obj2 = std::make_unique<DataObject>(pair2);

    auto array1 = std::make_unique<DataArray>();
    array1.get()->add(obj1);
    array1.get()->add(obj2);

    std::unique_ptr<IData> iArray1 = std::move(array1);

    std::unique_ptr<IData> root = std::make_unique<DataPair>("Request", iArray1);

    data_ = std::make_unique<DataObject>(root);
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
        return nullptr; // An empty Object

    std::size_t found = string.find(":");
    std::string key = std::string(string.begin(), string.begin() + found);
    std::string value = std::string(string.begin() + found + 1, string.end());

    key.erase(key.begin());
    key.erase(key.end() - 1);

    if (value[0] != '\"')
    {
        auto newValue = DataProtocol::parse_(value);
        std::unique_ptr<IData> entry = std::make_unique<DataPair>(key, newValue);
        return std::make_unique<DataObject>(entry);
    }
    else
    {
        value.erase(value.begin());
        value.erase(value.end() - 1);

        std::unique_ptr<IData> newValue = std::make_unique<DataString>(value);
        std::unique_ptr<IData> entry = std::make_unique<DataPair>(key, newValue);
        return std::make_unique<DataObject>(entry);
    }

    return nullptr;
}

std::unique_ptr<IData> DataProtocol::parseArray_(std::string string)
{
    if (string.length() == 0)
        return nullptr;

    //std::cout << "Array: " << string << std::endl;

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
        return nullptr;

    switch (string[0])
    {
        case '{': return DataProtocol::parseObject_(string);
        case '[': return DataProtocol::parseArray_(string);
        default: break;
    }

    return nullptr;
}
