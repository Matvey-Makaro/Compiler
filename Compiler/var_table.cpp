#include "var_table.h"
#include "string_functions.h"

#include <cassert>


VarTable::VarTable()
{
  offset = 0x103;
}

short VarTable::get_offset()
{
  return 0;
  return offset;
}

void VarTable::add_variable(const std::string& name, ID type, const std::string& value)
{
  add_variable(name, type, value, offset);
  short size = (type == ID::DW) ? 2 : 1;
  offset += size;
}

void VarTable::add_variable(const std::string& name, ID type, const std::string& value, short addr)
{
  variables.emplace_back(name, type, value, addr);
}

ID VarTable::get_type_of_variable(const std::string& name)
{
  for (const auto& var : variables)
  {
    if (strcicmp(var.name, name))
    {
      if (var.type == ID::DB)
        return ID::VAR_BYTE;
      else if (var.type == ID::DW)
        return ID::VAR_WORD;
      else assert(0);
    }
  }

  assert(0);
  return ID::NULL_ID;
}

short VarTable::get_address_of_variable(const std::string& name)
{
  for (const auto& var : variables)
    if (strcicmp(var.name, name))
      return var.addr;

  return static_cast<short>(ID::VAR);
}

