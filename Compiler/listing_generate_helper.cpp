#include "listing_generate_helper.h"

#include <algorithm>

const std::unordered_map<std::string, uint8_t> ListingGenerateHelper::reg_name_to_code = {
        {"al", 0b000},  {"ax", 0b000}, {"eax", 0b000}, {"rax", 0b000}, {"r8b", 0b000},   {"r8w", 0b000},   {"r8d", 0b000},   {"r8", 0b000},
        {"cl", 0b001},  {"cx", 0b001}, {"ecx", 0b001}, {"rcx", 0b001}, {"r9b", 0b001},   {"r9w", 0b001},   {"r9d", 0b001},   {"r9", 0b001},
        {"dl", 0b010},  {"dx", 0b010}, {"edx", 0b010}, {"rdx", 0b010}, {"r10b", 0b010},  {"r10w", 0b010},  {"r10d", 0b010},  {"r10", 0b010},
        {"bl", 0b011},  {"bx", 0b011}, {"ebx", 0b011}, {"rbx", 0b011}, {"r11b", 0b011},  {"r11w", 0b011},  {"r11d", 0b011},  {"r11", 0b011},
        {"spl", 0b100}, {"sp", 0b100}, {"esp", 0b100}, {"rsp", 0b100}, {"r12b", 0b100},  {"r12w", 0b100},  {"r12d", 0b100},  {"r12", 0b100},
        {"bpl", 0b101}, {"bp", 0b101}, {"ebp", 0b101}, {"rbp", 0b101}, {"r13b", 0b101},  {"r13w", 0b101},  {"r13d", 0b101},  {"r13", 0b101},
        {"sil", 0b110}, {"si", 0b110}, {"esi", 0b110}, {"rsi", 0b110}, {"r14b", 0b110},  {"r14w", 0b110},  {"r14d", 0b110},  {"r14", 0b110},
        {"dil", 0b110}, {"di", 0b111}, {"edi", 0b111}, {"rdi", 0b111}, {"r15b", 0b111},  {"r15w", 0b111},  {"r15d", 0b111},  {"r15", 0b111},
};

std::string ListingGenerateHelper::to_hex_string(uint64_t value)
{
    std::stringstream ss;
    ss << std::hex << std::uppercase << value;
    std::string str = ss.str();

    if (str.size() % 2 == 1)
        str = "0" + str;

    return str;
}

uint8_t ListingGenerateHelper::get_register_code(std::string reg_name)
{
    std::transform(cbegin(reg_name), cend(reg_name), begin(reg_name), tolower);
    return reg_name_to_code.at(reg_name);
}



