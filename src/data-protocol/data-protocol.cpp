#include <data-protocol/data-protocol.hpp>

DataProtocol::DataProtocol()
{
    ;
}

DataProtocol::~DataProtocol()
{
    ;
}

std::tuple<char*, size_t> DataProtocol::serialize()
{
    return std::make_tuple(nullptr, 0);
}

void DataProtocol::deserialize()
{
    ;
}

void DataProtocol::gather()
{

}

void DataProtocol::print()
{
    ;
}
