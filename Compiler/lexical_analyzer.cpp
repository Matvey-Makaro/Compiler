#include "lexical_analyzer.h"

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

std::vector<std::vector<std::string>> LexicalAnalyzer::get_text()
{
  return text;
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
          line.push_back(d->get_id());
      }
    }
    lexical_table.push_back(std::move(line));
  }
}
