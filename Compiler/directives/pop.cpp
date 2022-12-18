#include "pop.h"
#include "../exceptions/exceptions.h"

Pop::Pop() : Directive("pop", ID::POP)
{ }

bool Pop::check(int line_number, const LexicalLine & ids) const
{
    if (ids[0] != get_id())
        return false;

    constexpr int NECESSARY_ARGUMENTS_NUMBER = 1;

    if (ids.size() < NECESSARY_ARGUMENTS_NUMBER + 1)
        throw FewArgumentsException(line_number, NECESSARY_ARGUMENTS_NUMBER);
    if (ids.size() > NECESSARY_ARGUMENTS_NUMBER + 1)
        throw TooManyArgumentsException(line_number, NECESSARY_ARGUMENTS_NUMBER);

    for (size_t i = 1; i < ids.size(); i++)
    {
        if (!is_qword_register(ids[i]))
            throw WrongArgumentException(line_number);
    }

    return true;
}

std::string Pop::generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const
{
    if (lex_line[0] != get_id())
        return "";
    assert(is_qword_register(lex_line[1]));

    std::string result;
    // REX(id needed) 58 + rd
    if(lex_line[1] == ID::REGISTER_QWORD_ADDITIONAL)
    {
        uint8_t rex_prefix = 0b01000001;
        result += to_little_endian_string(rex_prefix);
    }
    uint8_t reg_id = ListingGenerateHelper::get_register_code(strs[1]);
    uint8_t opcode = 0x58 | reg_id;
    result += " " + to_little_endian_string(opcode);
    return result;
}