#pragma once

#include "IListingGenerator.h"
#include "aliases.h"
#include "var_table.h"

#include <vector>
#include <memory>
#include <string>

class ListingGenerator
{
public:
  ListingGenerator(const LexicalTable& lex_table, const VarTable& var_table, const Text& text);
  void generate(std::ostream& out);

private:
  std::string generateLine(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& part);


private:
  std::vector<std::unique_ptr<IListingGenerator>> directives;
  const LexicalTable& lexic_table;
  const VarTable& var_table;
  const Text& text;
};

