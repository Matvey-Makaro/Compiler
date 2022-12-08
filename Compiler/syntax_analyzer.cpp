#include "syntax_analyzer.h"
#include "directive.h"


SyntaxAnalyzer::SyntaxAnalyzer(const LexicalTable& lex_table) :
  lexical_table(lex_table)
{
  directives.push_back(std::make_unique<Pop>());
}

void SyntaxAnalyzer::analyze() const
{
  for (size_t i = 0; i < lexical_table.size(); i++)
    analyze_line(i, lexical_table[i]);
}

void SyntaxAnalyzer::analyze_line(int line_number, const LexicalLine& line) const
{
  for (const auto& directive : directives)
    if (directive->check(line_number, line))
      return;
}

