#pragma once

class DataProtocol
{
    public:
        DataProtocol();
        ~DataProtocol();

        void serialize();
        void deserialize();

        void gather();
        void print();
};
