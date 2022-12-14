#pragma once

#include "directives/IDs.h"
#include "string_functions.h"

#include <vector>
#include <string>
#include <memory>
#include <set>

using Text = std::vector<std::vector<std::string>>;
using LexicalLine = std::vector<ID>;
using LexicalTable = std::vector<LexicalLine>;
using RegisterNames = std::set<std::string, CaseInsensLess<std::string>>;