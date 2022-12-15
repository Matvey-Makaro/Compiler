#pragma once

#include "directives/IDs.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>

class ListingGenerateHelper
{
public:
    static std::string to_hex_string(uint64_t value);

    // TODO: Удалить.
    // static std::string to_little_endian_string(const std::string& str);

    static bool is_register_or_memory(ID id);
    static bool is_register(ID id);
    static bool is_memory(ID id);
    static bool is_byte_register(ID id);
    static bool is_word_register(ID id);
    static bool is_dword_register(ID id);
    static bool is_qword_register(ID id);
    static bool is_integer_number(ID id);
    static int8_t get_register_code(std::string reg_name);

    // TODO: Добавить поддержку сегментных регистров потом
    // int8_t get_segment_register_code(const std::string& reg_name);
private:
    const std::vector<std::string> segment_registers;
    static const std::unordered_map<std::string, int8_t> reg_name_to_code;

};

template<typename T>
std::string to_little_endian_string(T value)
{
    std::string result;
    for(size_t i = 0; i < sizeof(T) - 1; i++)
    {
        result += ListingGenerateHelper::to_hex_string(value & 0xFF) + " ";
        value >>= 8;
    }
    result += ListingGenerateHelper::to_hex_string(value & 0xFF);
    return result;
}