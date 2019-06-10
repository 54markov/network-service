#pragma once

#include <tuple>
#include <string>
#include <vector>
#include <memory>

/*
 * Interface class
 */
class IData
{
    public:
        virtual ~IData() = default;

        virtual void print() = 0;
        virtual std::string serialize() = 0;
};

/*
 * Each name is followed by ":" and the name/value pairs are separated by ",".
 */
class DataPair : public IData
{
    public:
        explicit DataPair(std::string name, std::unique_ptr<IData>& data);
        ~DataPair() = default;

        void print();

        std::string serialize();

    private:
        std::string name_;
        std::unique_ptr<IData> value_;
};

/*
 * Value representation
 */
class DataString : public IData
{
    public:
        explicit DataString(std::string string);
        ~DataString() = default;

        void print();

        std::string serialize();

    private:
        std::string string_;
};

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

        void add(std::unique_ptr<IData>& data);
        void print();
        std::string serialize();

    private:
        std::vector<std::unique_ptr<IData>> array_;
};

/*
 * An object is an unordered set of name/value pairs.
 * An object begins with "{" and ends with "}".
 */
class DataObject : public IData
{
    public:
        explicit DataObject(std::unique_ptr<IData>& data);
        ~DataObject() = default;

        void add(std::unique_ptr<IData>& data);

        void print();

        std::string serialize();

    private:
        std::vector<std::unique_ptr<IData>> pairs_;
};

class DataProtocol
{
    public:
        DataProtocol() = default;
        ~DataProtocol() = default;

        std::string serialize();
        void deserialize(std::string string);

        void gather1();
        void gather2();
        void print();

    private:
        std::unique_ptr<IData> data_;

        std::vector<std::string> split_(std::string s, const std::string& delimiter);
        std::unique_ptr<IData> parse_(std::string string);
        std::unique_ptr<IData> parseObject_(std::string string);
        std::unique_ptr<IData> parseArray_(std::string string);
};
