#pragma once

#include "exception_with_line_number.h"

class TooManyArgumentsException : public ExceptionWithLineNumber
{
public:
  TooManyArgumentsException(int line_number) :
    ExceptionWithLineNumber("Too many arguments", line_number)
  { }

  TooManyArgumentsException(int line_number, int necessary_arguments_num) :
    ExceptionWithLineNumber("Too many arguments, need " + std::to_string(necessary_arguments_num) + " args", line_number)
  { }
};