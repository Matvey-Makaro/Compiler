#include "listing_generator.h"
#include "listing_generate_helper.h"
#include "pop.h"


ListingGenerator::ListingGenerator(const LexicalTable& lex_table, const VarTable& var_table, const Text& text) :
  lexic_table(lex_table), var_table(var_table), text(text)
{
  // TODO: �������� ��������� ��������� ����, �� ����� ������� �� � ����� ����� � ����� ���������� �� � ������������.
  directives.push_back(std::make_unique<Pop>());
}

void ListingGenerator::generate(std::ostream& out)
{
  short offset = var_table.get_offset();
 
  for (size_t i = 0; i < lexic_table.size(); i++)
  {
    const auto& lex_line = lexic_table[i];
    std::string lineCode = generateLine(i, lex_line, text[i]);
    if (!ListingGenerateHelper::is_memory(lex_line[0]))
    {
      out << ListingGenerateHelper::to_hex_string(offset) << '\t';
      // TODO: ��� �������� ���� �� ����� ��������, �� ������ ���� �������.
      offset += std::count(cbegin(lineCode), cend(lineCode), ' ') + 1;
    }
    out << lineCode << '\n';
  }
}

std::string ListingGenerator::generateLine(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& part)
{
  for (size_t i = 0; i < directives.size(); i++)
  {
    std::string str = directives[i]->generate(line_number, lex_line, part, var_table);
    if (!str.empty())
      return str;
  }
  return "";
}
