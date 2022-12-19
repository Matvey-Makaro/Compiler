#pragma once

#include "directive.h"
#include "ISyntaxChecker.h"
#include "IListingGenerator.h"

#include <unordered_map>
#include <unordered_set>

class Add : public Directive, public ISyntaxChecker, public IListingGenerator
{
public:
    Add() : Directive("add", ID::ADD) {}

    virtual ~Add() {}
    virtual bool check(int line_number, const LexicalLine& ids) const;
    virtual std::string generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const override;

private:
    // rb - register byte, rw - register word, rd - register double word, rq - register quadra.
    std::string generate_for_rb_rb(const LexicalLine &lex_line, const std::vector<std::string> &strs) const;
    std::string generate_for_rw_rw(const LexicalLine &lex_line, const std::vector<std::string> &strs) const;
    std::string generate_for_rd_rd(const LexicalLine &lex_line, const std::vector<std::string> &strs) const;
    std::string generate_for_rq_rq(const LexicalLine &lex_line, const std::vector<std::string> &strs) const;
    std::string generate_for_rq_id(const LexicalLine &lex_line, const std::vector<std::string> &strs) const;
    std::string generate_for_rd_id(const LexicalLine &lex_line, const std::vector<std::string> &strs) const;
    std::string generate_for_rw_iw(const LexicalLine &lex_line, const std::vector<std::string> &strs) const;
    std::string generate_for_rb_ib(const LexicalLine &lex_line, const std::vector<std::string> &strs) const;

private:
    static const std::unordered_map<ID, std::unordered_set<ID>> valid_arguments;
};

