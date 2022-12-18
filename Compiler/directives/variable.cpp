#include "variable.h"
#include "../exceptions/exceptions.h"

#include <regex>

Variable::Variable() : Directive("", ID::VAR)
{ }

bool Variable::is_directive(const std::string &dir_name) const
{
    static const std::regex r("^[a-zA-Z0-9_]+$");
    return regex_match(dir_name, r);
}

bool Variable::check(int lineNumber, const LexicalLine &ids) const
{
    if(ids[0] != get_id())
        return false;

    constexpr size_t expected_ids_size = 3;
    if(ids.size() < expected_ids_size)
        throw FewArgumentsException(lineNumber, expected_ids_size - 1);
    if(ids.size() < expected_ids_size)
        throw TooManyArgumentsException(lineNumber, expected_ids_size - 1);

    if(ids[2] != ID::INTEGER_NUMBER)
        throw WrongArgumentException(lineNumber);
    if(!is_define_variable(ids[1]))
        throw WrongArgumentException(lineNumber);

    return true;
}

std::string Variable::generate(int line_number, const LexicalLine &lex_line, const std::vector<std::string> &strs,
                               const VarTable &var_table) const
{
    ID var_id = lex_line[0];
    const std::string& var_name = strs[0];
    const std::string& var_value = strs[2];

    if(!is_memory(var_id))
        return "";

    std::string result;
    auto offset = var_table.get_address_of_variable(var_name);
    result += ListingGenerateHelper::to_hex_string(offset) + " ";

    if(var_id == ID::VAR_BYTE)
        result += to_8byte_hex_str(var_value);
    else if(var_id == ID::VAR_WORD)
        result += to_16byte_hex_str(var_value);
    else if(var_id == ID::VAR_DWORD)
        result += to_32byte_hex_str(var_value);
    else if(var_id == ID::VAR_QWORD)
        result += to_64byte_hex_str(var_value);
    else assert(0);

    return result;
}

