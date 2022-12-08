#pragma once

#include "string_functions.h"
#include "ISyntaxChecker.h"
#include "aliases.h"
#include "IDs.h"

#include <string>
#include <set>
#include <utility>
#include <stdexcept>


class Directive
{
public:
  Directive(const std::string& directive_name, ID directive_id) :
    name(directive_name), id(directive_id)
  {}

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

class Pop : public Directive, public ISyntaxChecker
{
public:
  Pop() : Directive("pop", ID::POP) { }

  virtual bool check(int lineNumber, const LexicalLine& ids) const
  {
    if (ids[0] != get_id())
      return false;

    // TODO: Заменить на своё исключение FewArgumentsException.
    if (ids.size() < 2)
      throw std::logic_error("Few arguments.");

    for (int i = 1; i < ids.size(); i++)
    {
      // TODO: Заменить на REGISTER_QWORD
      // TODO: Заменить на свой exception WrongArgumentsException.
      if (ids[i] != ID::REGISTER_WORD)
        throw std::logic_error("Wrong argument.");
    }
    
    return true;
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
  ByteRegister() : Register({ "al", "ah", "bl", "bh" }) {}

  virtual ID get_id() const override 
  { 
    return ID::REGISTER_BYTE; 
  }
};

class WordRegister : public Register
{
public:
  WordRegister() : Register({ "ax", "bx" }) {}

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