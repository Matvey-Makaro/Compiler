#pragma once

#include "directives/IDs.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <type_traits>

class ListingGenerateHelper
{
public:
    static std::string to_hex_string(uint64_t value);
    static uint8_t get_register_code(std::string reg_name);

    // TODO: Добавить поддержку сегментных регистров потом
    // int8_t get_segment_register_code(const std::string& reg_name);
private:
    const std::vector<std::string> segment_registers;
    static const std::unordered_map<std::string, uint8_t> reg_name_to_code;

};

template<typename T>
std::string to_little_endian_string(T value)
{
    static_assert(std::is_integral<T>::value, "Integral required");

    auto unsigned_value = static_cast<std::make_unsigned_t<T>>(value);
    std::string result;
    for(size_t i = 0; i < sizeof(T) - 1; i++)
    {
        result += ListingGenerateHelper::to_hex_string(unsigned_value & 0xFF) + " ";
        unsigned_value >>= 8;
    }
    result += ListingGenerateHelper::to_hex_string(unsigned_value & 0xFF);
    return result;
}