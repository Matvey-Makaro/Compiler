#include "mov.h"
#include "../listing_generate_helper.h"
#include "../exceptions/exceptions.h"

const std::unordered_map<ID, std::unordered_set<ID>> Mov::valid_arguments = {
        {ID::REGISTER_BYTE, {ID::REGISTER_BYTE, ID::REGISTER_BYTE_ADDITIONAL}},
        {ID::REGISTER_WORD, {ID::REGISTER_WORD, ID::REGISTER_WORD_ADDITIONAL}},
        {ID::REGISTER_DWORD, {ID::REGISTER_DWORD, ID::REGISTER_DWORD_ADDITIONAL}},
        {ID::REGISTER_QWORD, {ID::REGISTER_QWORD, ID::REGISTER_QWORD_ADDITIONAL}},
        {ID::REGISTER_BYTE_ADDITIONAL, {ID::REGISTER_BYTE, ID::REGISTER_BYTE_ADDITIONAL}},
        {ID::REGISTER_WORD_ADDITIONAL, {ID::REGISTER_WORD, ID::REGISTER_WORD_ADDITIONAL}},
        {ID::REGISTER_DWORD_ADDITIONAL, {ID::REGISTER_DWORD, ID::REGISTER_DWORD_ADDITIONAL}},
        {ID::REGISTER_QWORD_ADDITIONAL, {ID::REGISTER_QWORD, ID::REGISTER_QWORD_ADDITIONAL}},
};



Mov::Mov() : Directive("mov", ID::MOV)
{ }

bool Mov::check(int line_number, const LexicalLine & ids) const
{
    if (ids[0] != get_id())
        return false;

    constexpr int NECESSARY_ARGUMENTS_NUMBER = 2;

    if (ids.size() < NECESSARY_ARGUMENTS_NUMBER + 2)
        throw FewArgumentsException(line_number, NECESSARY_ARGUMENTS_NUMBER);
    if (ids.size() > NECESSARY_ARGUMENTS_NUMBER + 2)
        throw TooManyArgumentsException(line_number, NECESSARY_ARGUMENTS_NUMBER);

    if (ids[2] != ID::COMMA)
        throw CommaExpectedException(line_number);

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
    if (ListingGenerateHelper::is_byte_register(lex_line[1]) && ListingGenerateHelper::is_byte_register(lex_line[3]))
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
        uint8_t rm_reg = ListingGenerateHelper::get_register_code(strs[1]);
        uint8_t reg_opcode_reg = ListingGenerateHelper::get_register_code(strs[3]);
        uint8_t modRM_code = 0b11000000 | (reg_opcode_reg << 3) | rm_reg;
        result += ListingGenerateHelper::to_hex_string(modRM_code); // modR/M
    }
    else if (ListingGenerateHelper::is_word_register(lex_line[1]) && ListingGenerateHelper::is_word_register(lex_line[3]))
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
        uint8_t rm_reg = ListingGenerateHelper::get_register_code(strs[1]);
        uint8_t reg_opcode_reg = ListingGenerateHelper::get_register_code(strs[3]);
        uint8_t modRM_code = 0b11000000 | (reg_opcode_reg << 3) | rm_reg;
        result += ListingGenerateHelper::to_hex_string(modRM_code); // modR/M
    }
    else if(ListingGenerateHelper::is_dword_register(lex_line[1]) && ListingGenerateHelper::is_dword_register(lex_line[3]))
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
        uint8_t rm_reg = ListingGenerateHelper::get_register_code(strs[1]);
        uint8_t reg_opcode_reg = ListingGenerateHelper::get_register_code(strs[3]);
        uint8_t modRM_code = 0b11000000 | (reg_opcode_reg << 3) | rm_reg;
        result += ListingGenerateHelper::to_hex_string(modRM_code); // modR/M
    }
    else if(ListingGenerateHelper::is_qword_register(lex_line[1]) && ListingGenerateHelper::is_qword_register(lex_line[3]))
    {
        uint8_t rex_prefix = 0b01001000;    //0b0100WRXB
        if(lex_line[1] == ID::REGISTER_QWORD_ADDITIONAL)
            rex_prefix |= 0b00000001;
        if(lex_line[3] == ID::REGISTER_QWORD_ADDITIONAL)
            rex_prefix |= 0b00000100;

        result += ListingGenerateHelper::to_hex_string(rex_prefix); // REX prefix
        result += " 89 "; // opcode
        uint8_t rm_reg = ListingGenerateHelper::get_register_code(strs[1]);
        uint8_t reg_opcode_reg = ListingGenerateHelper::get_register_code(strs[3]);
        uint8_t modRM_code = 0b11000000 | (reg_opcode_reg << 3) | rm_reg;
        result += ListingGenerateHelper::to_hex_string(modRM_code); // modR/M
    }
    else assert(0);

    return result;
}