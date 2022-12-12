#include "mov.h"
#include "listing_generate_helper.h"

Mov::Mov() : Directive("mov", ID::MOV)
{ }

bool Mov::check(int lineNumber, const LexicalLine & ids) const
{
  if (ids[0] != get_id())
    return false;

  // TODO: Заменить на своё исключение FewArgumentsException.
  if (ids.size() < 3)
    throw std::logic_error("Few arguments.");
  if (ids.size() > 3)
    throw std::logic_error("Too many arguments");

  for (size_t i = 1; i < ids.size(); i++)
  {
    // TODO: Заменить на REGISTER_QWORD
    // TODO: Заменить на свой exception WrongArgumentsException.
    if(!ListingGenerateHelper::is_register_or_memory(ids[i]))
      throw std::logic_error("Wrong argument.");
  }

  return true;
}

std::string Mov::generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const
{
  return std::string();
}
