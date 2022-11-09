#pragma once

#include <iostream>
#include <vector>

class LexicalAnalyzer
{
public:
  void split(std::istream& in);
  std::vector<std::vector<std::string>> get_text();
private:
  std::vector<std::vector<std::string>> text;
};