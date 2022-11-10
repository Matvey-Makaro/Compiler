#pragma once

#include "directive.h"

#include <iostream>
#include <vector>
#include <memory>

using Text = std::vector<std::vector<std::string>>;
using LexicalLine = std::vector<ID>;
using LexicalTable = std::vector<LexicalLine>;
using Directives = std::vector<std::unique_ptr<Directive>>;

class LexicalAnalyzer
{
public:
  LexicalAnalyzer();

  void split(std::istream& in);
  Text get_text();
  LexicalTable get_lexical_table() { return lexical_table; }
  void parse();

private:
  Text text;
  LexicalTable lexical_table;

  Directives directives;
};
