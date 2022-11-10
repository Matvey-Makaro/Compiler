#pragma once

#include "string_functions.h"

#include <string>
#include <set>
#include <utility>

enum class ID
{
  NULL_ID = -1,

  DB = 0,
  DW = 1,

  COMMA = 5,

  ADD = 10,
  MUL = 11,
  PUSH = 12,
  POP = 13,
  IDIV = 14,

  NUMBER_BYTE = 100,
  NUMBER_WORD = 101,
  NUMBER_INFINITY = 102,

  REGISTER_BYTE = 200,
  REGISTER_WORD = 201,

  VAR = 500,
  VAR_BYTE = 501,
  VAR_WORD = 502
};

using RegisterNames = std::set<std::string, CaseInsensLess<std::string>>;

class Directive
{
public:
  Directive(const std::string& directive_name, ID directive_id) :
    name(directive_name), id(directive_id)
  {}

  ID get_id() const { return id; }

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
  ByteRegister() : Register({ "al", "bl" }) {}
};

class WordRegister : public Register
{
public:
  WordRegister() : Register({ "ax", "bx" }) {}
};