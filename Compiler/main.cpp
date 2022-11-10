#include "lexical_analyzer.h"

#include <iostream>
#include <fstream>

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
  auto text = lexical_analyzer.get_text();
  cout << "Text: " << endl;
  for (const auto& str : text)
  {
    for (const auto& word : str)
      cout << word << ' ';
    cout << '\n';
  }

  cout << "\nTable:\n";
  lexical_analyzer.parse();
  auto table = lexical_analyzer.get_lexical_table();
  for (const auto& line : table)
  {
    for (const auto el : line)
      cout << static_cast<int>(el) << ' ';
    cout << '\n';
  }

  return 0;
}