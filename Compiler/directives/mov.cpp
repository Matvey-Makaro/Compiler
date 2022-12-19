#include "mov.h"
#include "../listing_generate_helper.h"
#include "../exceptions/exceptions.h"
#include "../string_functions.h"

#include <sstream>

const std::unordered_map<ID, std::unordered_set<ID>> Mov::valid_arguments = {
        {ID::REGISTER_BYTE, {ID::REGISTER_BYTE, ID::REGISTER_BYTE_ADDITIONAL, ID::INTEGER_NUMBER, ID::VAR_BYTE, ID::VAR_WORD, ID::VAR_DWORD, ID::VAR_QWORD}},
        {ID::REGISTER_WORD, {ID::REGISTER_WORD, ID::REGISTER_WORD_ADDITIONAL, ID::INTEGER_NUMBER, ID::VAR_BYTE, ID::VAR_WORD, ID::VAR_DWORD, ID::VAR_QWORD}},
        {ID::REGISTER_DWORD, {ID::REGISTER_DWORD, ID::REGISTER_DWORD_ADDITIONAL, ID::INTEGER_NUMBER, ID::VAR_BYTE, ID::VAR_WORD, ID::VAR_DWORD, ID::VAR_QWORD}},
        {ID::REGISTER_QWORD, {ID::REGISTER_QWORD, ID::REGISTER_QWORD_ADDITIONAL, ID::INTEGER_NUMBER, ID::VAR_BYTE, ID::VAR_WORD, ID::VAR_DWORD, ID::VAR_QWORD}},
        {ID::REGISTER_BYTE_ADDITIONAL, {ID::REGISTER_BYTE, ID::REGISTER_BYTE_ADDITIONAL, ID::INTEGER_NUMBER, ID::VAR_BYTE, ID::VAR_WORD, ID::VAR_DWORD, ID::VAR_QWORD}},
        {ID::REGISTER_WORD_ADDITIONAL, {ID::REGISTER_WORD, ID::REGISTER_WORD_ADDITIONAL, ID::INTEGER_NUMBER, ID::VAR_BYTE, ID::VAR_WORD, ID::VAR_DWORD, ID::VAR_QWORD}},
        {ID::REGISTER_DWORD_ADDITIONAL, {ID::REGISTER_DWORD, ID::REGISTER_DWORD_ADDITIONAL, ID::INTEGER_NUMBER, ID::VAR_BYTE, ID::VAR_WORD, ID::VAR_DWORD, ID::VAR_QWORD}},
        {ID::REGISTER_QWORD_ADDITIONAL, {ID::REGISTER_QWORD, ID::REGISTER_QWORD_ADDITIONAL, ID::INTEGER_NUMBER, ID::VAR_BYTE, ID::VAR_WORD, ID::VAR_DWORD, ID::VAR_QWORD}},
};



Mov::Mov() : Directive("mov", ID::MOV)
{ }

bool Mov::check(int line_number, const LexicalLine & ids) const
{
    if (ids[0] != get_id())
        return false;

    if(ids.size() > 2 && ids[2] != ID::COMMA)
        throw CommaExpectedException(line_number);

    constexpr int NECESSARY_ARGUMENTS_NUMBER = 2;
    if (ids.size() < NECESSARY_ARGUMENTS_NUMBER + 2)
        throw FewArgumentsException(line_number, NECESSARY_ARGUMENTS_NUMBER);
    if (ids.size() > NECESSARY_ARGUMENTS_NUMBER + 2)
        throw TooManyArgumentsException(line_number, NECESSARY_ARGUMENTS_NUMBER);

    try
    {
        if(valid_arguments.at(ids[1]).count(ids[3]) == 0)
            throw WrongArgumentException(line_number);
    }
    catch (const std::exception&)
    {
        throw WrongArgumentException(line_number);
    }

    return true;
}

std::string Mov::generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const
{
    if (lex_line[0] != get_id())
        return "";

    std::string result;
    if(is_register(lex_line[3]))
    {
        if (is_byte_register(lex_line[1]) && is_byte_register(lex_line[3]))
        {
            bool is_rex_prefix_needed = false;
            uint8_t rex_prefix = 0b01000000;    //0b0100WRXB
            if(lex_line[1] == ID::REGISTER_BYTE_ADDITIONAL)
            {
                rex_prefix |= 0b00000001;
                is_rex_prefix_needed = true;
            }
            if(lex_line[3] == ID::REGISTER_BYTE_ADDITIONAL)
            {
                rex_prefix |= 0b00000100;
                is_rex_prefix_needed = true;
            }
            if(is_rex_prefix_needed)
                result += ListingGenerateHelper::to_hex_string(rex_prefix) + " ";

            // 88 /r | MOV r/m8,r8
            result += "88 "; // opcode
            auto modRM_code = ListingGenerateHelper::get_modRM_for_reg_reg(strs[1], strs[3]);
            result += ListingGenerateHelper::to_hex_string(modRM_code); // modR/M
        }
        else if (is_word_register(lex_line[1]) && is_word_register(lex_line[3]))
        {
            result += "66 ";  // prefix

            bool is_rex_prefix_needed = false;
            uint8_t rex_prefix = 0b01000000;    //0b0100WRXB
            if(lex_line[1] == ID::REGISTER_WORD_ADDITIONAL)
            {
                rex_prefix |= 0b00000001;
                is_rex_prefix_needed = true;
            }
            if(lex_line[3] == ID::REGISTER_WORD_ADDITIONAL)
            {
                rex_prefix |= 0b00000100;
                is_rex_prefix_needed = true;
            }
            if(is_rex_prefix_needed)
                result += ListingGenerateHelper::to_hex_string(rex_prefix) + " ";
            // 66 89/r | MOV r/m16,r16
            result += "89 ";  // opcode
            auto modRM_code = ListingGenerateHelper::get_modRM_for_reg_reg(strs[1], strs[3]);
            result += ListingGenerateHelper::to_hex_string(modRM_code);
        }
        else if(is_dword_register(lex_line[1]) && is_dword_register(lex_line[3]))
        {
            bool is_rex_prefix_needed = false;
            uint8_t rex_prefix = 0b01000000;    //0b0100WRXB
            if(lex_line[1] == ID::REGISTER_DWORD_ADDITIONAL)
            {
                rex_prefix |= 0b00000001;
                is_rex_prefix_needed = true;
            }
            if(lex_line[3] == ID::REGISTER_DWORD_ADDITIONAL)
            {
                rex_prefix |= 0b00000100;
                is_rex_prefix_needed = true;
            }
            if(is_rex_prefix_needed)
                result += ListingGenerateHelper::to_hex_string(rex_prefix) + " ";

            result += "89 ";  // opcode
            auto modRM_code = ListingGenerateHelper::get_modRM_for_reg_reg(strs[1], strs[3]);
            result += ListingGenerateHelper::to_hex_string(modRM_code);
        }
        else if(is_qword_register(lex_line[1]) && is_qword_register(lex_line[3])) {
            uint8_t rex_prefix = 0b01001000;    //0b0100WRXB
            if (lex_line[1] == ID::REGISTER_QWORD_ADDITIONAL)
                rex_prefix |= 0b00000001;
            if (lex_line[3] == ID::REGISTER_QWORD_ADDITIONAL)
                rex_prefix |= 0b00000100;

            result += ListingGenerateHelper::to_hex_string(rex_prefix); // REX prefix
            result += " 89 "; // opcode
            auto modRM_code = ListingGenerateHelper::get_modRM_for_reg_reg(strs[1], strs[3]);
            result += ListingGenerateHelper::to_hex_string(modRM_code);
        }
        else assert(0);
    }
    else
    {
        if(is_integer_number(lex_line[3]))
        {
            if(is_qword_register(lex_line[1]))
            {
                uint8_t rex_prefix = 0b01001000;    //0b0100WRXB
                if (lex_line[1] == ID::REGISTER_QWORD_ADDITIONAL)
                    rex_prefix |= 0b00000001;

                result += ListingGenerateHelper::to_hex_string(rex_prefix); // REX prefix
                // TODO: Если число влазит в int32_t, то можно использовать mov с opcode C7, пока что всегда использую с opcode B8
                uint8_t opcode = 0xB8;
                opcode |= ListingGenerateHelper::get_register_code(strs[1]);
                result += " " + to_little_endian_string(opcode) + " ";

                result += to_64byte_hex_str(strs[3]);
            }
            else if (is_dword_register(lex_line[1]))
            {
                if(lex_line[1] == ID::REGISTER_DWORD_ADDITIONAL)
                {
                    uint8_t rex_prefix = 0b01000001;
                    result += to_little_endian_string(rex_prefix) + " ";
                }

                uint8_t opcode = 0xB8;
                opcode |= ListingGenerateHelper::get_register_code(strs[1]);
                result += to_little_endian_string(opcode) + " ";

                result += to_32byte_hex_str(strs[3]);
            }
            else if(is_word_register(lex_line[1]))
            {
                result += "66 ";
                if(lex_line[1] == ID::REGISTER_WORD_ADDITIONAL)
                {
                    uint8_t rex_prefix = 0b01000001;
                    result += to_little_endian_string(rex_prefix) + " ";
                }
                uint8_t opcode = 0xB8;
                opcode |= ListingGenerateHelper::get_register_code(strs[1]);
                result += to_little_endian_string(opcode) + " ";

                result += to_16byte_hex_str(strs[3]);
            }
            else if(is_byte_register(lex_line[1]))
            {
                if(lex_line[1] == ID::REGISTER_BYTE_ADDITIONAL)
                {
                    uint8_t rex_prefix = 0b01000001;
                    result += to_little_endian_string(rex_prefix) + " ";
                }
                uint8_t opcode = 0xB0;
                opcode |= ListingGenerateHelper::get_register_code(strs[1]);
                result += to_little_endian_string(opcode) + " ";

                result +=to_8byte_hex_str(strs[3]);
            }
            else assert(0);
        }
        else if(is_memory(lex_line[3]))
        {
            if(is_qword_register(lex_line[1]))
            {
                uint8_t rex_prefix = 0b01001000;    //0b0100WRXB
                if (lex_line[1] == ID::REGISTER_QWORD_ADDITIONAL)
                    rex_prefix |= 0b00000001;

                result += ListingGenerateHelper::to_hex_string(rex_prefix); // REX prefix
                // TODO: Если число влазит в int32_t, то можно использовать mov с opcode C7, пока что всегда использую с opcode B8
                uint8_t opcode = 0xB8;
                opcode |= ListingGenerateHelper::get_register_code(strs[1]);
                result += " " + to_little_endian_string(opcode) + " ";

                auto address = var_table.get_address_of_variable(strs[3]);
                result += to_little_endian_string(static_cast<uint64_t>(address));
            }
            else if (is_dword_register(lex_line[1]))
            {
                if(lex_line[1] == ID::REGISTER_DWORD_ADDITIONAL)
                {
                    uint8_t rex_prefix = 0b01000001;
                    result += to_little_endian_string(rex_prefix) + " ";
                }

                uint8_t opcode = 0xB8;
                opcode |= ListingGenerateHelper::get_register_code(strs[1]);
                result += to_little_endian_string(opcode) + " ";

                auto address = var_table.get_address_of_variable(strs[3]);
                result += to_little_endian_string(static_cast<uint32_t>(address));
            }
            else if(is_word_register(lex_line[1]))
            {
                result += "66 ";
                if(lex_line[1] == ID::REGISTER_WORD_ADDITIONAL)
                {
                    uint8_t rex_prefix = 0b01000001;
                    result += to_little_endian_string(rex_prefix) + " ";
                }
                uint8_t opcode = 0xB8;
                opcode |= ListingGenerateHelper::get_register_code(strs[1]);
                result += to_little_endian_string(opcode) + " ";

                auto address = var_table.get_address_of_variable(strs[3]);
                result += to_little_endian_string(static_cast<uint16_t>(address));
            }
            else if(is_byte_register(lex_line[1]))
            {
                if(lex_line[1] == ID::REGISTER_BYTE_ADDITIONAL)
                {
                    uint8_t rex_prefix = 0b01000001;
                    result += to_little_endian_string(rex_prefix) + " ";
                }
                uint8_t opcode = 0xB0;
                opcode |= ListingGenerateHelper::get_register_code(strs[1]);
                result += to_little_endian_string(opcode) + " ";

                auto address = var_table.get_address_of_variable(strs[3]);
                result += to_little_endian_string(static_cast<uint8_t>(address));
            }
            else assert(0);
        }

    }

    return result;
}
