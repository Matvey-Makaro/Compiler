#pragma once

#include "aliases.h"
#include "var_table.h"

#include <string>

class IListingGenerator
{
public:
  virtual std::string generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const = 0;
};
