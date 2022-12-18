#pragma once

#include "directive.h"

class Comma : public Directive
{
public:
    Comma() : Directive(",", ID::COMMA) {}
};