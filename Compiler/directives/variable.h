#pragma once

#include "directive.h"

class Variable : public Directive, public ISyntaxChecker, public IListingGenerator
{
public:
    Variable();

    virtual bool is_directive(const std::string& dir_name) const override;
    virtual bool check(int lineNumber, const LexicalLine& ids) const override;
    virtual std::string generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const override;
};

