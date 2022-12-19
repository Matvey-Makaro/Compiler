#include "add.h"
#include "../exceptions/exceptions.h"

const std::unordered_map<ID, std::unordered_set<ID>> Add::valid_arguments = {
        {ID::REGISTER_BYTE, {ID::REGISTER_BYTE, ID::REGISTER_BYTE_ADDITIONAL, ID::INTEGER_NUMBER}},
        {ID::REGISTER_WORD, {ID::REGISTER_WORD, ID::REGISTER_WORD_ADDITIONAL, ID::INTEGER_NUMBER}},
        {ID::REGISTER_DWORD, {ID::REGISTER_DWORD, ID::REGISTER_DWORD_ADDITIONAL, ID::INTEGER_NUMBER}},
        {ID::REGISTER_QWORD, {ID::REGISTER_QWORD, ID::REGISTER_QWORD_ADDITIONAL, ID::INTEGER_NUMBER}},
        {ID::REGISTER_BYTE_ADDITIONAL, {ID::REGISTER_BYTE, ID::REGISTER_BYTE_ADDITIONAL, ID::INTEGER_NUMBER}},
        {ID::REGISTER_WORD_ADDITIONAL, {ID::REGISTER_WORD, ID::REGISTER_WORD_ADDITIONAL, ID::INTEGER_NUMBER}},
        {ID::REGISTER_DWORD_ADDITIONAL, {ID::REGISTER_DWORD, ID::REGISTER_DWORD_ADDITIONAL, ID::INTEGER_NUMBER}},
        {ID::REGISTER_QWORD_ADDITIONAL, {ID::REGISTER_QWORD, ID::REGISTER_QWORD_ADDITIONAL, ID::INTEGER_NUMBER}},
};

bool Add::check(int line_number, const LexicalLine &ids) const
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

std::string Add::generate(int line_number, const LexicalLine &lex_line, const std::vector<std::string> &strs,
                          const VarTable &var_table) const
{
    if (lex_line[0] != get_id())
    return "";

    std::string result;
    if(is_register(lex_line[3]))
    {
        if (is_byte_register(lex_line[1]) && is_byte_register(lex_line[3]))
            return generate_for_rb_rb(lex_line, strs);
        else if (is_word_register(lex_line[1]) && is_word_register(lex_line[3]))
            return generate_for_rw_rw(lex_line, strs);
        else if(is_dword_register(lex_line[1]) && is_dword_register(lex_line[3]))
            return generate_for_rd_rd(lex_line, strs);
        else if(is_qword_register(lex_line[1]) && is_qword_register(lex_line[3]))
            return generate_for_rq_rq(lex_line, strs);
        else assert(0);
    }
    else
    {
        if (is_integer_number(lex_line[3]))
        {
            if (is_qword_register(lex_line[1]))
                return generate_for_rq_id(lex_line, strs);
            else if (is_dword_register(lex_line[1]))
                return generate_for_rd_id(lex_line, strs);
            else if (is_word_register(lex_line[1]))
                return generate_for_rw_iw(lex_line, strs);
            else if (is_byte_register(lex_line[1]))
                return generate_for_rb_ib(lex_line, strs);
            else assert(0);
        }
    }
}

std::string Add::generate_for_rb_rb(const LexicalLine &lex_line, const std::vector<std::string> &strs) const {
    std::string result;
    bool is_rex_prefix_needed = false;
    uint8_t rex_prefix = 0b01000000;    //0b0100WRXB
    if (lex_line[1] == ID::REGISTER_BYTE_ADDITIONAL)
    {
        rex_prefix |= 0b00000001;
        is_rex_prefix_needed = true;
    }
    if (lex_line[3] == ID::REGISTER_BYTE_ADDITIONAL)
    {
        rex_prefix |= 0b00000100;
        is_rex_prefix_needed = true;
    }
    if (is_rex_prefix_needed)
        result += ListingGenerateHelper::to_hex_string(rex_prefix) + " ";

    // 00 /r | ADD r/m8,r8
    result += "00 "; // opcode
    auto modRM_code = ListingGenerateHelper::get_modRM_for_reg_reg(strs[1], strs[3]);
    result += ListingGenerateHelper::to_hex_string(modRM_code);
    return result;
}

std::string Add::generate_for_rw_rw(const LexicalLine &lex_line, const std::vector<std::string> &strs) const
{
    std::string result;
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
    // 66 01/r | ADD r/m16,r16
    result += "01 ";  // opcode
    auto modRM_code = ListingGenerateHelper::get_modRM_for_reg_reg(strs[1], strs[3]);
    result += ListingGenerateHelper::to_hex_string(modRM_code);
    return result;
}

std::string Add::generate_for_rd_rd(const LexicalLine &lex_line, const std::vector<std::string> &strs) const
{
    std::string result;
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

    result += "01 ";  // opcode
    auto modRM_code = ListingGenerateHelper::get_modRM_for_reg_reg(strs[1], strs[3]);
    result += ListingGenerateHelper::to_hex_string(modRM_code); // modR/M
    return result;
}

std::string Add::generate_for_rq_rq(const LexicalLine &lex_line, const std::vector<std::string> &strs) const
{
    std::string result;
    uint8_t rex_prefix = 0b01001000;    //0b0100WRXB
    if (lex_line[1] == ID::REGISTER_QWORD_ADDITIONAL)
        rex_prefix |= 0b00000001;
    if (lex_line[3] == ID::REGISTER_QWORD_ADDITIONAL)
        rex_prefix |= 0b00000100;

    result += ListingGenerateHelper::to_hex_string(rex_prefix); // REX prefix
    result += " 01 "; // opcode
    auto modRM_code = ListingGenerateHelper::get_modRM_for_reg_reg(strs[1], strs[3]);
    result += ListingGenerateHelper::to_hex_string(modRM_code); // modR/M
    return result;
}

std::string Add::generate_for_rq_id(const LexicalLine &lex_line, const std::vector<std::string> &strs) const
{
    std::string result;
    uint8_t rex_prefix = 0b01001000;    //0b0100WRXB
    if (lex_line[1] == ID::REGISTER_QWORD_ADDITIONAL)
        rex_prefix |= 0b00000001;

    result += ListingGenerateHelper::to_hex_string(rex_prefix); // REX prefix
    uint8_t opcode = 0x81;
    result += " " + to_little_endian_string(opcode) + " ";
    auto modRM = ListingGenerateHelper::get_modRM_for_reg_imm(strs[1]);
    result += to_little_endian_string(modRM) + " ";
    result += to_32byte_hex_str(strs[3]);
    return result;
}

std::string Add::generate_for_rd_id(const LexicalLine &lex_line, const std::vector<std::string> &strs) const
{
    std::string result;
    if (lex_line[1] == ID::REGISTER_DWORD_ADDITIONAL)
    {
        uint8_t rex_prefix = 0b01000001;
        result += to_little_endian_string(rex_prefix) + " ";
    }

    uint8_t opcode = 0x81;
    result += to_little_endian_string(opcode) + " ";
    auto modRM = ListingGenerateHelper::get_modRM_for_reg_imm(strs[1]);
    result += to_little_endian_string(modRM) + " ";
    result += to_32byte_hex_str(strs[3]);
    return result;
}

std::string Add::generate_for_rw_iw(const LexicalLine &lex_line, const std::vector<std::string> &strs) const
{
    std::string result;
    result += "66 ";
    if (lex_line[1] == ID::REGISTER_WORD_ADDITIONAL)
    {
        uint8_t rex_prefix = 0b01000001;
        result += to_little_endian_string(rex_prefix) + " ";
    }
    uint8_t opcode = 0x81;
    result += to_little_endian_string(opcode) + " ";
    auto modRM = ListingGenerateHelper::get_modRM_for_reg_imm(strs[1]);
    result += to_little_endian_string(modRM) + " ";
    result += to_16byte_hex_str(strs[3]);
    return result;
}

std::string Add::generate_for_rb_ib(const LexicalLine &lex_line, const std::vector<std::string> &strs) const
{
    std::string result;
    uint8_t rex_prefix = 0b01000000;
    if (lex_line[1] == ID::REGISTER_BYTE_ADDITIONAL)
        rex_prefix |= 0b00000001;

    result += to_little_endian_string(rex_prefix) + " ";
    uint8_t opcode = 0x80;
    result += to_little_endian_string(opcode) + " ";
    auto modRM = ListingGenerateHelper::get_modRM_for_reg_imm(strs[1]);
    result += to_little_endian_string(modRM) + " ";
    result += to_8byte_hex_str(strs[3]);
    return result;
}
