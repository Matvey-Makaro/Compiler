#pragma once

#include "var.h"
#include "directives/IDs.h"

#include <vector>
#include <string>

class VarTable
{
public:
    VarTable();

    short get_offset() const;
    void add_variable(const std::string& name, ID type, const std::string& value);
    void add_variable(const std::string& name, ID type, const std::string& value, short addr);
    ID get_type_of_variable(const std::string& name) const;
    short get_address_of_variable(const std::string& name) const;

private:
    short offset;
    // TODO: Возможно стоит заменить на map для более быстрого поска переменной по имени
    std::vector<Var> variables;
};

//short VarTable::offset = 0x103;