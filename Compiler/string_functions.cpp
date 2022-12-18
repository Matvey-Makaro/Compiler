#include "string_functions.h"
#include "listing_generate_helper.h"

#include <string>
#include <algorithm>
#include <sstream>

// String comparison case insensitive.
bool strcicmp(const std::string& lhs, const std::string& rhs)
{
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(), [](const char lhs, const char rhs) {
        return tolower(lhs) == tolower(rhs);
    });
}

std::string to_8byte_hex_str(const std::string& value)
{
    std::stringstream ss(value);
    if(value[0] == '-')
    {
        int16_t number;
        ss >> number;
        return to_little_endian_string(static_cast<int8_t>(number));
    }
    else
    {
        uint16_t number;
        ss >> number;
        return to_little_endian_string(static_cast<uint8_t>(number));
    }
}

std::string to_16byte_hex_str(const std::string& value)
{
    std::stringstream ss(value);
    if(value[0] == '-')
    {
        int16_t number;
        ss >> number;
        return to_little_endian_string(number);
    }
    else
    {
        uint16_t number;
        ss >> number;
        return to_little_endian_string(number);
    }
}

std::string to_32byte_hex_str(const std::string& value)
{
    std::stringstream ss(value);
    if(value[0] == '-')
    {
        int32_t number;
        ss >> number;
        return to_little_endian_string(number);
    }
    else
    {
        uint32_t number;
        ss >> number;
        return to_little_endian_string(number);
    }
}

std::string to_64byte_hex_str(const std::string& value)
{
    std::stringstream ss(value);
    if(value[0] == '-')
    {
        int64_t number;
        ss >> number;
        return to_little_endian_string(number);
    }
    else
    {
        uint64_t number;
        ss >> number;
        return  to_little_endian_string(number);
    }
}
