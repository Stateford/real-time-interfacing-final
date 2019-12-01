#pragma once

#include <stdexcept>


class FontException : public std::runtime_error
{
public:
    explicit FontException(const char* what) : std::runtime_error(what) {};
    explicit FontException(const std::string& what) : std::runtime_error(what) {};
};