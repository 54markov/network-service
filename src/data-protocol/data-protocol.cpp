#include <data-protocol/data-protocol.hpp>

#include <iostream>

std::tuple<const char*, size_t> DataProtocol::serialize()
{
    return std::make_tuple(str_.c_str(), str_.size());
}

void DataProtocol::deserialize(const char* buf, const size_t size)
{
    str_ = std::string(buf);
}

void DataProtocol::gather()
{
	str_ = "hello";
}

void DataProtocol::print()
{
    std::cout << str_ << std::endl;
}
