#include "var_table.h"
#include "string_functions.h"

#include <cassert>


VarTable::VarTable()
{
    offset = 0x0;
}

short VarTable::get_offset() const
{
    return offset;
}

void VarTable::add_variable(const std::string& name, ID type, const std::string& value)
{
    add_variable(name, type, value, offset);
    short size = 0;
    if(type == ID::DB)
        size = sizeof(uint8_t);
    else if(type == ID::DW)
        size = sizeof(uint16_t);
    else if(type == ID::DD)
        size = sizeof(uint32_t);
    else if(type == ID::DQ)
        size = sizeof(uint64_t);
    else assert(0);

    offset += size;
}

void VarTable::add_variable(const std::string& name, ID type, const std::string& value, short addr)
{
    variables.emplace_back(name, type, value, addr);
}

ID VarTable::get_type_of_variable(const std::string& name) const
{
    for (const auto& var : variables)
    {
        if (strcicmp(var.name, name))
        {
            if (var.type == ID::DB)
                return ID::VAR_BYTE;
            else if (var.type == ID::DW)
                return ID::VAR_WORD;
            else if(var.type == ID::DD)
                return ID::VAR_DWORD;
            else if(var.type == ID::DQ)
                return ID::VAR_QWORD;
            else assert(0);
        }
    }

    assert(0);
    return ID::VAR;
}

short VarTable::get_address_of_variable(const std::string& name) const
{
    for (const auto& var : variables)
        if (strcicmp(var.name, name))
            return var.addr;

    assert(0);
}
