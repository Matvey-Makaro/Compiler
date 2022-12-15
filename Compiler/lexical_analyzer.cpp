#include "lexical_analyzer.h"
#include "directives/directives.h"

#include <iostream>
#include <vector>
#include <string>
#include <utility>


LexicalAnalyzer::LexicalAnalyzer()
{
    constexpr size_t NUM_OF_DIRECTIVE = 10;
    directives.reserve(NUM_OF_DIRECTIVE);

    directives.push_back(std::make_unique<Add>());
    directives.push_back(std::make_unique<Mul>());
    directives.push_back(std::make_unique<Comma>());
    directives.push_back(std::make_unique<ByteRegister>());
    directives.push_back(std::make_unique<WordRegister>());
    directives.push_back(std::make_unique<DWordRegister>());
    directives.push_back(std::make_unique<QWordRegister>());
    directives.push_back(std::make_unique<ByteRegisterAdditional>());
    directives.push_back(std::make_unique<WordRegisterAdditional>());
    directives.push_back(std::make_unique<DWordRegisterAdditional>());
    directives.push_back(std::make_unique<QWordRegisterAdditional>());
    directives.push_back(std::make_unique<IntegerNumber>());
    directives.push_back(std::make_unique<Pop>());
    directives.push_back(std::make_unique<Mov>());
}

void LexicalAnalyzer::split(std::istream& in)
{
    std::string str;
    std::vector<std::string> line;
    std::string word;
    size_t start_new_word = 0;
    while (std::getline(in, str))
    {
        if (str.empty())
            continue;

        size_t start = str.find_first_not_of(' ');
        size_t end = str.find_last_not_of(' ');
        start_new_word = start;
        for (size_t i = start; i <= end; i++)
        {
            if (str[i] == ' ')
            {
                line.push_back(str.substr(start_new_word, i - start_new_word));
                start_new_word = str.find_first_not_of(' ', i);
                i = start_new_word - 1;
            }
            else if (str[i] == ',')
            {
                if (start_new_word != i)
                    line.push_back(str.substr(start_new_word, i - start_new_word));

                line.push_back(",");
                start_new_word = str.find_first_not_of(' ', i + 1);
                i = start_new_word - 1;
            }
        }

        line.push_back(str.substr(start_new_word, end - start_new_word + 1));
        text.push_back(std::move(line));
    }
}

Text& LexicalAnalyzer::get_text()
{
    return text;
}

LexicalTable& LexicalAnalyzer::get_lexical_table()
{
    return lexical_table;
}

VarTable& LexicalAnalyzer::get_var_table()
{
    return var_table;
}

void LexicalAnalyzer::parse()
{
    LexicalLine line;
    for (const auto& str : text)
    {
        for (const auto& word : str)
        {
            for (const auto& d : directives)
            {
                if (d->is_directive(word))
                {
                    line.push_back(d->get_id());
                    break;
                }

            }
        }
        lexical_table.push_back(std::move(line));
    }
}

void LexicalAnalyzer::analyze()
{
    analyze_variables();
}

void LexicalAnalyzer::analyze_variables()
{
    for (size_t i = 0; i < lexical_table.size(); i++)
        add_variable_to_table(lexical_table[i], i);

    for (size_t i = 0; i < lexical_table.size(); i++)
        assign_variable_types(lexical_table[i]);
}

void LexicalAnalyzer::add_variable_to_table(const LexicalLine& line, int line_number)
{
    if (line[0] != ID::VAR)
        return;
    if (line.size() != 3)
        return;

    const auto& parts = text[line_number];  // TODO: Возможно line_number-1
    if (parts.size() != 3)
        return;

    std::string var_name = parts[0];
    ID type = line[1];
    std::string value = parts[2];
    var_table.add_variable(var_name, type, value);
}

void LexicalAnalyzer::assign_variable_types(LexicalLine& line)
{
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == ID::VAR)
        {
            const auto& parts = text[i];
            if (parts.size() != line.size())
                continue;

            line[i] = var_table.get_type_of_variable(parts[i]);
        }
    }
}
