#pragma once

#include "ISyntaxChecker.h"
#include "aliases.h"

#include <vector>
#include <memory>

class SyntaxAnalyzer
{
public:
  SyntaxAnalyzer(const LexicalTable& lex_table);

  void analyze() const;

private:
  void analyze_line(int line_number, const LexicalLine& line) const;

private:
  std::vector<std::unique_ptr<ISyntaxChecker>> directives;
  const LexicalTable& lexical_table;
};

