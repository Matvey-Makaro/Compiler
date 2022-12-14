#pragma once

#include "directives/directive.h"
#include "var_table.h"
#include "aliases.h"

#include <iostream>


using Directives = std::vector<std::unique_ptr<Directive>>;

class LexicalAnalyzer
{
public:
    LexicalAnalyzer();

    void split(std::istream& in);
    Text& get_text();
    LexicalTable& get_lexical_table();
    VarTable& get_var_table();
    void parse();
    void analyze();

private:
    // void analyze_line(int line_number);
    void analyze_variables();
    void add_variable_to_table(const LexicalLine& line, int line_number);
    void assign_variable_types(LexicalLine& line);

private:
    Text text;
    LexicalTable lexical_table;
    Directives directives;
    VarTable var_table;
};
