#include <iostream>
#include <string>
#include <vector>
#include <memory>

class IData
{
    public:
        virtual ~IData() = default;

        virtual void print() = 0;
        virtual std::string serialize() = 0;
        virtual void desrialize(std::string string) = 0;
};

/*
 * Each name is followed by ":" and the name/value pairs are separated by ",".
 */
class DataPair : public IData
{
    public:
        DataPair(std::string name, std::unique_ptr<IData>& data)
        {
            name.erase(name.begin());
            name.erase(name.end() - 1);

            name_ = name;
            value_ = std::move(data);
        }
        ~DataPair() = default;

        void print()
        {
            std::cout << name_ << ":";
            value_->print();
        }

        std::string serialize()
        {
            return "\"" + name_ + "\"" + ":" + value_->serialize();
        }

        void desrialize(std::string string)
        {
            // TODO
        }

    private:
        std::string name_;
        std::unique_ptr<IData> value_;
};


class DataString : public IData
{
    public:
        explicit DataString(std::string string)
        {
            string.erase(string.begin());
            string.erase(string.end() - 1);

            string_ = string;
        }

        ~DataString() = default;

        void print()
        {
            std::cout << string_;
        }

        std::string serialize()
        {
            return "\"" + string_ + "\"";
        }

        void desrialize(std::string string)
        {
            // TODO
        }

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
        explicit DataArray() = default;
        ~DataArray() = default;

        void add(std::unique_ptr<IData>& data)
        {
            array_.push_back(std::move(data));
        }

        void print()
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

        std::string serialize()
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

        void desrialize(std::string string)
        {
            // TODO
        }

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
        explicit DataObject() = default;
        explicit DataObject(std::unique_ptr<IData>& data)
        {
            pairs_.push_back(std::move(data));
        }

        ~DataObject() = default;

        void add(std::unique_ptr<IData>& data)
        {
            pairs_.push_back(std::move(data));
        }

        void print()
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

        std::string serialize()
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

        void desrialize(std::string string)
        {
            // TODO
        }

    private:
        std::vector<std::unique_ptr<IData>> pairs_;
};

std::vector<std::string> split(std::string s, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    auto first = 1;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        if (delimiter != "," && first--)
            token = s.substr(0, pos + 1);
        else
            token = s.substr(0, pos);

        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    tokens.push_back(s);
    return tokens;
}

std::unique_ptr<IData> parse(std::string string)
{
    if (string.length() == 0)
        return nullptr;

    switch (string[0])
    {
        case '{':
        {
            //std::cout << "Object: " << string << std::endl;

            string.erase(string.begin());
            string.erase(string.end() - 1);

            std::size_t found = string.find(":");
            std::string key = std::string(string.begin(), string.begin() + found);
            std::string value = std::string(string.begin() + found + 1, string.end());

            if (value[0] != '\"')
            {
                auto newValue = parse(value);
                std::unique_ptr<IData> entry = std::make_unique<DataPair>(key, newValue);
                return std::make_unique<DataObject>(entry);
            }
            else
            {
                std::unique_ptr<IData> newValue = std::make_unique<DataString>(value);
                std::unique_ptr<IData> entry = std::make_unique<DataPair>(key, newValue);
                return std::make_unique<DataObject>(entry);
            }
            break;
        }
        case '[':
        {
            //std::cout << "Array: " << string << std::endl;
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

            auto dataArray = std::make_unique<DataArray>();

            auto a = split(string, delimiter);

            for (auto i : a)
            {
                if (delimiter != ",")
                {
                    auto entry = parse(i);
                    dataArray.get()->add(entry);
                }
                else
                {
                    std::unique_ptr<IData> entry = std::make_unique<DataString>(i);
                    dataArray.get()->add(entry);
                }
            }

            return dataArray;
            break;
        }
        default: break;
    }

    return nullptr;
}

int main(int argc, char const *argv[])
{

    const std::vector<std::string> test = {
        "{\"root\":\"value0\"}",
        "{\"root\":{\"key1\":\"value1\"}}",
        "{\"root\":[\"v0\",\"v0\"]}",
        "{\"root\":[[\"v0\",\"v0\"],[\"v0\",\"v0\"]]}",
        "{\"root\":{\"key1\":[\"v1\",\"v1\"]}}",
        "{\"root\":{\"key1\":[[\"v1\",\"v1\"],[\"v1\",\"v1\"]]}}",
        "{\"root\":[{\"key1\":[\"v1\",\"v1\"]},{\"key2\":[[\"v2\",\"v2\"],[\"v2\",\"v2\"]]}]}",
        "{\"root\":[{\"key1\":\"value1\"},{\"key2\":\"value2\"}]}",
        "{\"root\":[{\"key1\":[\"v1\",\"v1\"]},{\"key2\":\"value2\"}]}",
        "{\"root\":{\"k1\":{\"k2\":{\"k3\":{\"k4\":\"v4\"}}}}}",
        "{\"root\":{\"k1\":{\"k2\":{\"k3\":[{\"k4\":[\"v4\",\"v4\"]},{\"k5\":[\"v5\",\"v5\"]}]}}}}"
    };

    for (auto i : test)
    {
        std::cout << "Raw   : " << i << std::endl;
        auto dataObject = parse(i);
        auto serializeStr = dataObject->serialize();
        auto rc = !i.compare(serializeStr);
        std::cout << "Serial: " << serializeStr << (rc ? " Ok" : " Fail") << std::endl;
        std::cout << "Parsed: ";
        dataObject->print();
        std::cout << std::endl << std::endl;
    }

    return 0;
}
