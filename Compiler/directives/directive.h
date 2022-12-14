#pragma once

#include "../string_functions.h"
#include "ISyntaxChecker.h"
#include "IListingGenerator.h"
#include "aliases.h"
#include "IDs.h"
#include "../listing_generate_helper.h"

#include <string>
#include <set>
#include <utility>
#include <stdexcept>
#include <cassert>


class Directive
{
public:
    Directive(const std::string& directive_name, ID directive_id);
    virtual ~Directive() {}
    virtual ID get_id() const;
    virtual bool is_directive(const std::string& dir_name) const;

protected:
    std::string name;
    ID id;
};

class Add : public Directive
{
public:
    Add() : Directive("add", ID::ADD) {}

};

class Mul : public Directive
{
public:
    Mul() : Directive("mul", ID::MUL) {}
};

class Comma : public Directive
{
public:
    Comma() : Directive(",", ID::COMMA) {}
};



class Register : public Directive
{
public:
    Register(RegisterNames reg_names) :
            Directive("", ID::NULL_ID), register_names(std::move(reg_names))
    { }

    virtual bool is_directive(const std::string& dir_name) const override
    {
        return register_names.count(dir_name);
    }

protected:
    const RegisterNames register_names;
};

class ByteRegister : public Register
{
public:
    ByteRegister() : Register({ "al", "ah", "bl", "bh", "cl", "ch", "dl", "dh", "spl", "bpl", "sil", "dil",
                                "r8b", "r9b" , "r10b" , "r11b" , "r12b" , "r13b" , "r14b" , "r15b" }) {}

    virtual ID get_id() const override
    {
        return ID::REGISTER_BYTE;
    }
};

class WordRegister : public Register
{
public:
    WordRegister() : Register({ "ax", "bx", "cx", "dx", "sp", "bp", "si", "di", "r8w", "r9w" , "r10w" , "r11w" , "r12w" , "r13w" , "r14w" , "r15w" }) {}

    virtual ID get_id() const override
    {
        return ID::REGISTER_WORD;
    }
};

class DWordRegister : public Register
{
    DWordRegister() : Register({ "eax", "ebx" }) {}

    virtual ID get_id() const override
    {
        // TODO: Âîçâðàùàòü ID äëÿ REGISTER_DWORD.
        return ID::NULL_ID;
    }
};

class QWordRegister : public Register
{
    QWordRegister() : Register({"rax", "rbx"}) {}

    virtual ID get_id() const override
    {
        // TODO: Âîçâðàùàòü ID äëÿ REGISTER_DWORD.
        return ID::NULL_ID;
    }
};
