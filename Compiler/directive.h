#pragma once

#include "string_functions.h"
#include "ISyntaxChecker.h"
#include "IListingGenerator.h"
#include "aliases.h"
#include "IDs.h"
#include "listing_generate_helper.h"

#include <string>
#include <set>
#include <utility>
#include <stdexcept>
#include <cassert>


class Directive
{
public:
  Directive(const std::string& directive_name, ID directive_id) :
    name(directive_name), id(directive_id)
  {}

  virtual ~Directive() {}

  virtual ID get_id() const { return id; }

  virtual bool is_directive(const std::string& dir_name) const
  {
    return strcicmp(name, dir_name);
  }

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

class Pop : public Directive, public ISyntaxChecker, public IListingGenerator
{
public:
  Pop() : Directive("pop", ID::POP) { }
  virtual ~Pop() {}

  virtual bool check(int lineNumber, const LexicalLine& ids) const
  {
    if (ids[0] != get_id())
      return false;

    // TODO: Заменить на своё исключение FewArgumentsException.
    if (ids.size() < 2)
      throw std::logic_error("Few arguments.");

    for (size_t i = 1; i < ids.size(); i++)
    {
      // TODO: Заменить на REGISTER_QWORD
      // TODO: Заменить на свой exception WrongArgumentsException.
      if (ids[i] != ID::REGISTER_WORD)
        throw std::logic_error("Wrong argument.");
    }
    
    return true;
  }

  virtual std::string generate(int line_number, const LexicalLine& lex_line, const std::vector<std::string>& strs, const VarTable& var_table) const override
  {
    if (lex_line[0] != get_id())
      return "";

    // TODO: Изменить генерацию кода для POP, должно использовать только 64-разрядные регистры.
    if (lex_line[1] == ID::REGISTER_WORD)
    {
      // TODO: Обработать сегментные регистры.
      int8_t reg_id = ListingGenerateHelper::get_register_code(strs[1]);
      // reg16/32  01011reg
      int8_t machine_code = static_cast<int8_t>(0b01011000 | reg_id);
      return ListingGenerateHelper::to_hex_string(machine_code);
    }

    assert(0);
    return "";
  }
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
    // TODO: Возвращать ID для REGISTER_DWORD.
    return ID::NULL_ID;
  }
};

class QWordRegister : public Register
{
  QWordRegister() : Register({"rax", "rbx"}) {}

  virtual ID get_id() const override
  {
    // TODO: Возвращать ID для REGISTER_DWORD.
    return ID::NULL_ID;
  }
};
