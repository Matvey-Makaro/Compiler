#pragma once

#include "IDs.h"

#include <string>


struct Var
{
  std::string name;
  ID type;
  std::string value;
  short addr;

  Var(const std::string& name, ID type, const std::string& value, short addr):
    name(name), type(type), value(value), addr(addr)
  { }
};

