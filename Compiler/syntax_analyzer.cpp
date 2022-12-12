#include "syntax_analyzer.h"
#include "pop.h"
#include "mov.h"


SyntaxAnalyzer::SyntaxAnalyzer(const LexicalTable& lex_table) :
  lexical_table(lex_table)
{
  constexpr size_t NUM_OF_DIRECTIVE = 10;
  directives.reserve(NUM_OF_DIRECTIVE);

  directives.emplace_back(std::unique_ptr<ISyntaxChecker>(new Pop()));
  directives.emplace_back(std::unique_ptr<ISyntaxChecker>(new Mov()));
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

