#pragma once

#include "exception_with_line_number.h"

class FewArgumentsException : public ExceptionWithLineNumber
{
public:
  FewArgumentsException(int line_number) :
    ExceptionWithLineNumber("Few arguments", line_number)
  { }

  FewArgumentsException(int line_number, int necessary_arguments_num) :
    ExceptionWithLineNumber("Few arguments, need " + std::to_string(necessary_arguments_num) + " args", line_number)
  { }
};
