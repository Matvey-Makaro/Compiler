#pragma once

#include "exception_with_line_number.h"

class WrongArgumentException : public ExceptionWithLineNumber
{
public:
    WrongArgumentException(int line_number) :
            ExceptionWithLineNumber("Wrong argument", line_number)
    { }
};