#pragma once
#include "directive.h"
#include "ISyntaxChecker.h"
#include "IListingGenerator.h"

#include <string>

class Pop : public Directive, public ISyntaxChecker, public IListingGenerator
{
public:
    Pop();
    virtual ~Pop() {}
    virtual bool check(int lineNumber, const LexicalLine& ids) const;
    virtual std::string generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const override;
};