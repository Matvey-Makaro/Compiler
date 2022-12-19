#pragma once

#include "../string_functions.h"
#include "ISyntaxChecker.h"
#include "IListingGenerator.h"
#include "aliases.h"
#include "IDs.h"
#include "../listing_generate_helper.h"

#include <string>
#include <set>
#include <utility>
#include <stdexcept>
#include <cassert>


class Directive
{
public:
    Directive(const std::string& directive_name, ID directive_id);
    virtual ~Directive() {}
    virtual ID get_id() const;
    virtual bool is_directive(const std::string& dir_name) const;

protected:
    std::string name;
    ID id;
};

class Mul : public Directive
{
public:
    Mul() : Directive("mul", ID::MUL) {}
};

