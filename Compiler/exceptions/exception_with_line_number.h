#pragma once

#include <stdexcept>
#include <string>

class ExceptionWithLineNumber : public std::logic_error
{
public:
    ExceptionWithLineNumber(const std::string& message, int line_number) :
            std::logic_error(message + " at line " + std::to_string(line_number))
    { }
};