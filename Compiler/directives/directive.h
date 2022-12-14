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
    ByteRegister() : Register({ "al", "ah", "bl", "bh", "cl", "ch", "dl", "dh", "spl", "bpl", "sil", "dil" }) {}

    virtual ID get_id() const override
    {
        return ID::REGISTER_BYTE;
    }
};

class WordRegister : public Register
{
public:
    WordRegister() : Register({ "ax", "bx", "cx", "dx", "sp", "bp", "si", "di" }) {}

    virtual ID get_id() const override
    {
        return ID::REGISTER_WORD;
    }
};

class DWordRegister : public Register
{
public:
    DWordRegister() : Register({ "eax", "ebx", "ecx", "edx", "esp", "ebp", "esi", "edi" }) {}

    virtual ID get_id() const override
    {
        return ID::REGISTER_DWORD;
    }
};

class QWordRegister : public Register
{
public:
    QWordRegister() : Register({ "rax", "rbx", "rcx", "rdx", "rsp", "rbp", "rsi", "rdi" }) {}

    virtual ID get_id() const override
    {
        return ID::REGISTER_QWORD;
    }
};

class ByteRegisterAdditional : public Register
{
public:
    ByteRegisterAdditional() : Register({"r8b", "r9b" , "r10b" , "r11b" , "r12b" , "r13b" , "r14b" , "r15b" }) {}

    virtual ID get_id() const override
    {
        return ID::REGISTER_BYTE_ADDITIONAL;
    }
};

class WordRegisterAdditional : public Register
{
public:
    WordRegisterAdditional() : Register({"r8w", "r9w" , "r10w" , "r11w" , "r12w" , "r13w" , "r14w" , "r15w" }) {}

    virtual ID get_id() const override
    {
        return ID::REGISTER_WORD_ADDITIONAL;
    }
};

class DWordRegisterAdditional : public Register
{
public:
    DWordRegisterAdditional() : Register({"r8d", "r9d" , "r10d" , "r11d" , "r12d" , "r13d" , "r14d" , "r15d" }) {}

    virtual ID get_id() const override
    {
        return ID::REGISTER_DWORD_ADDITIONAL;
    }
};

class QWordRegisterAdditional : public Register
{
public:
    QWordRegisterAdditional() : Register({"r8", "r9" , "r10" , "r11" , "r12" , "r13" , "r14" , "r15" }) {}

    virtual ID get_id() const override
    {
        return ID::REGISTER_QWORD_ADDITIONAL;
    }
};