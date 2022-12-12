#include "pop.h"
#include "few_arguments_exception.h"
#include "too_many_arguments_exception.h"
#include "wrong_argument_exception.h"

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
    // TODO: Заменить на REGISTER_QWORD
    if (ids[i] != ID::REGISTER_WORD)
      throw WrongArgumentException(line_number);
  }

  return true;
}

std::string Pop::generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const
{
  if (lex_line[0] != get_id())
    return "";

  // TODO: Изменить генерацию кода для POP, должно использовать только 64-разрядные регистры.
  if (lex_line[1] == ID::REGISTER_WORD)
  {
    // TODO: Обработать сегментные регистры.
    int8_t reg_id = ListingGenerateHelper::get_register_code(strs[1]);
    // reg16/32  01011reg
    int8_t machine_code = static_cast<int8_t>(0b01011000 | reg_id);
    return ListingGenerateHelper::to_hex_string(machine_code);
  }

  assert(0);
  return "";
}
