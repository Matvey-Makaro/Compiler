#pragma once

#include "directive.h"
#include "ISyntaxChecker.h"
#include "IListingGenerator.h"

class Mov : public Directive, public ISyntaxChecker, public IListingGenerator
{
public:
  Mov();
  virtual ~Mov() {}
  virtual bool check(int lineNumber, const LexicalLine& ids) const;
  virtual std::string generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const override;

};

