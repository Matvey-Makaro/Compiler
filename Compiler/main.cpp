#include "lexical_analyzer.h"
#include "syntax_analyzer.h"
#include "listing_generator.h"

#include <iostream>
#include <fstream>
#include <sstream>  // TODO: For test, delete later.
#include <unordered_map>  // TODO: For test, delete later.
#include "listing_generate_helper.h" // TODO: For test, delete later.

using namespace std;

int main()
{
  std::string fName = "test.txt";
  std::fstream fs(fName);
  if (!fs.is_open())
  {
    cerr << "File \"" << fName << "\" doesn't open." << endl;
    return -1;
  }

  LexicalAnalyzer lexical_analyzer;
  lexical_analyzer.split(fs);
  const auto& text = lexical_analyzer.get_text();
  cout << "Text: " << endl;
  for (const auto& str : text)
  {
    for (const auto& word : str)
      cout << word << ' ';
    cout << '\n';
  }

  cout << "\nTable:\n";
  lexical_analyzer.parse();
  const auto& table = lexical_analyzer.get_lexical_table();
  for (const auto& line : table)
  {
    for (const auto el : line)
      cout << static_cast<int>(el) << ' ';
    cout << '\n';
  }

  SyntaxAnalyzer syntax_analyzer(table);
  try
  {
    syntax_analyzer.analyze();
  }
  catch (const std::exception& ex)
  {
    cerr << ex.what() << endl;
    return -1;
  }

  cout << "Generated text:" << endl;
  const auto& var_table = lexical_analyzer.get_var_table();
  ListingGenerator listing_generator(table, var_table, text);
  listing_generator.generate(cout);
  
  

 /* std::stringstream ss("ssfdsf");
  ss << std::hex;
  int x;
  ss >> x;
  string tmp;
  ss >> tmp;
  cout << "TMP: " <<  tmp << endl;
  if (ss.fail() || !ss.str().empty())
    cout << "SS failed" << endl;
  cout << "X: " << x << endl;

  const std::unordered_map<std::string, int8_t> reg_name_to_code = { {"al", 0b000} };
  cout << static_cast<int>(reg_name_to_code.at("al")) << endl;*/

  return 0;
}