#include "mov.h"
#include "../listing_generate_helper.h"
#include "../exceptions/exceptions.h"

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

    // TODO: Добавить проверку, чтобы операнды были нужного размера. И добавить память. И проверить на нужную конфигурацию параметров.
    if (!ListingGenerateHelper::is_register(ids[1]) || !ListingGenerateHelper::is_register(ids[3]))
        throw WrongArgumentException(line_number);

    return true;
}

std::string Mov::generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const
{
    if (lex_line[0] != get_id())
        return "";

    std::string result;
    if (lex_line[1] == ID::REGISTER_BYTE && lex_line[3] == ID::REGISTER_BYTE)
    {
        // 88 /r | MOV r/m8,r8
        result += "88 "; // opcode
        uint8_t rm_reg = ListingGenerateHelper::get_register_code(strs[1]);
        uint8_t reg_opcode_reg = ListingGenerateHelper::get_register_code(strs[3]);
        uint8_t modRM_code = 0b11000000 | (reg_opcode_reg << 3) | rm_reg;
        result += ListingGenerateHelper::to_hex_string(modRM_code); // modR/M
    }
    else if (lex_line[1] == ID::REGISTER_WORD && lex_line[3] == ID::REGISTER_WORD)
    {
        // 66 89/r | MOV r/m16,r16
        result += "66 ";  // prefix
        result += "89 ";  // opcode
        uint8_t rm_reg = ListingGenerateHelper::get_register_code(strs[1]);
        uint8_t reg_opcode_reg = ListingGenerateHelper::get_register_code(strs[3]);
        uint8_t modRM_code = 0b11000000 | (reg_opcode_reg << 3) | rm_reg;
        result += ListingGenerateHelper::to_hex_string(modRM_code); // modR/M
    }
    else assert(0);

    return result;
}
