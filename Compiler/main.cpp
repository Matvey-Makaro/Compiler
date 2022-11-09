#include "LexicalAnalyzer.h"

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

  for (const auto& str : text)
  {
    for (const auto& word : str)
      cout << word << ' ';
    cout << '\n';
  }

  return 0;
}