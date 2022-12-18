#pragma once

#include "directive.h"

class DB : public Directive
{
public:
    DB() : Directive("DB", ID::DB)
    { }
};

class DW : public Directive
{
public:
    DW() : Directive("DW", ID::DW)
    { }
};

class DD : public Directive
{
public:
    DD() : Directive("DD", ID::DD)
    { }
};

class DQ : public Directive
{
public:
    DQ() : Directive("DQ", ID::DQ)
    { }
};
