#pragma once

#include "aliases.h"

class ISyntaxChecker
{
public:
  virtual bool check(int lineNumber, const LexicalLine& ids) const  = 0;

  virtual ~ISyntaxChecker() {};
};