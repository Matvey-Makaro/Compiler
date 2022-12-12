#pragma once

#include "exception_with_line_number.h"

class CommaExpectedException : public ExceptionWithLineNumber
{
public:
  CommaExpectedException(int line_number) :
    ExceptionWithLineNumber("Comma expected", line_number)
  { }
};
