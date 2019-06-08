#pragma once

#include <string>
#include <string.h>

class Exception : public std::exception
{
    private:
        int code_;
        std::string err_;

    public:
        Exception(const std::string& err, const int code);
        ~Exception() = default;

        virtual const char* what() const noexcept override;
        int code() const noexcept;
};
